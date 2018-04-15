#include <Platform/Window.h>
#include <Platform/Time.h>

#include <Input/Keyboard.h>

#include <Graphics/Font.h>
#include <Graphics/Renderer2D.h>

using namespace Gene;
using namespace Gene::Platform;
using namespace Gene::Graphics;
using namespace Gene::Input;

float Random(float min, float max) //range : [min, max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    const float range = min - max;
    float random = range * ((((float)rand()) / (float)RAND_MAX)) + min;
    return random;
}

class Application {
protected:
    Window *Window;

public:
    Application() {}
    
    virtual void Update(const GameTime& time) = 0;
    virtual void Render() = 0;
    virtual void Initalize() = 0;

    void Start(int w, int h, const char *title)
    {
        Window = Window::CreateWindow({ w, h, title });
        Window->Create();
        Initalize();

        Window->Show();

        GameTime time;
        time.Init();
        while (Window->Running())
        {
            time.StartFrame();
            Window->PollEvents();
            Update(time);
            Window->Clear();
            Render();
            Window->SwapBuffers();
            time.EndFrame();
            time.Sleep(1000.f / 60.f);
        }
    }
};

struct KeyboardScheme 
{
    Keys UpKey;
    Keys DownKey;

    KeyboardScheme(Keys up, Keys down) : UpKey(up), DownKey(down) {}
    KeyboardScheme() {}
};

static KeyboardScheme PlayerOneKeyboard = KeyboardScheme(Keys::W, Keys::S);
static KeyboardScheme PlayerTwoKeyboard = KeyboardScheme(Keys::UpArrow, Keys::DownArrow);

static const int PaddleWidth = 1.5;
static const int PaddleHeight = 10;

static const float AreaWidth = 800 / 16.f;
static const float AreaHeight = 600 / 16.f;

static const float PaddleSpeed = 0.05f;

static const int BallWidth = 1;
static const int BallHeight = 1;

static const float BallSpeedRange = 0.02f;

static bool GameOver = false;
static bool Paused = false;

static Font *MyFont;

enum class PaddleController
{
    Cpu, Human
};

enum class Side  
{
    Left, Right
};

class Ball
{
private:
    Vector2 m_Position;
    Vector2 m_Velocity;

public:
    void Start()
    {
        m_Position.X = (AreaWidth / 2) - (BallWidth / 2);
        m_Position.Y = (AreaHeight / 2) - (BallHeight / 2);

        m_Velocity.X = BallSpeedRange;
        m_Velocity.Y = BallSpeedRange;
    }

    void Update(const GameTime& time)
    {
        if (m_Position.X + BallWidth > AreaWidth || m_Position.X < 0) GameOver = true;
        if (m_Position.Y + BallHeight > AreaHeight || m_Position.Y < 0) m_Velocity.Y = -m_Velocity.Y;

        if (GameOver)
        {
            m_Velocity.X = 0;
            m_Velocity.Y = 0;

            m_Position.X = (AreaWidth / 2) - (BallWidth / 2);
            m_Position.Y = (AreaHeight / 2) - (BallHeight / 2);
        }

        m_Position.X += m_Velocity.X * time.DeltaInMilliSeconds();
        m_Position.Y += m_Velocity.Y * time.DeltaInMilliSeconds();
    }

    void Render(Renderer2D *renderer)
    {
        renderer->FillRectangle(m_Position, BallWidth, BallHeight, Color::White);
    }

    Vector2 GetPosition() {
        return m_Position;
    }

    Vector2 GetVelocity() {
        return m_Velocity;
    }

    void SetVelocity(Vector2 vec2) {
        m_Velocity = vec2;
    }
};

class Paddle;

bool BallInsidePaddle(Ball& ball, Paddle& paddle);

class Paddle
{
private:
    PaddleController m_Controller;
    KeyboardScheme m_KeyScheme;
    Side m_Side;

    Vector2 m_Position;
    Vector2 m_Velocity;

    void CheckWallColliders()
    {
        if (m_Position.Y + PaddleHeight > AreaHeight) 
            m_Position.Y = AreaHeight - PaddleHeight;

        if (m_Position.Y < 0)
            m_Position.Y = 0;
    }

    void UpdateAsHuman(const GameTime& time, Ball& ball)
    {
        KeyboardState state = Keyboard::GetState();

        if (state.IsKeyDown(m_KeyScheme.UpKey))
        {
            m_Velocity.Y = -PaddleSpeed;
        }
        else if (state.IsKeyDown(m_KeyScheme.DownKey))
        {
            m_Velocity.Y = PaddleSpeed;
        }
        else {
            m_Velocity.Y = 0;
        }

        if (BallInsidePaddle(ball, *this))
        {
            Vector2 bVel = ball.GetVelocity();
            Vector2 newVel(-bVel.X, bVel.Y);
            ball.SetVelocity(newVel);
        }

        m_Position.X += m_Velocity.X * time.DeltaInMilliSeconds();
        m_Position.Y += m_Velocity.Y * time.DeltaInMilliSeconds();


        CheckWallColliders();
    }

    void Setup()
    {
        switch (m_Side)
        {
        case Side::Left:
            m_Position = Vector2(1, 1);
            break;
        case Side::Right:
            m_Position = Vector2(AreaWidth - (1 + PaddleWidth), 1);
            break;
        }
    }
public:

    Vector2 GetPosition()
    {
        return m_Position;
    }

    void Update(const GameTime& time, Ball& ball)
    {
        switch (m_Controller)
        {
        case PaddleController::Human:
            UpdateAsHuman(time, ball);
            break;
        }
    }

    void Render(Renderer2D *renderer)
    {
        renderer->FillRectangle(m_Position, PaddleWidth, PaddleHeight, Color::White);
    }

    void SetAsAI(Side side)
    {
        m_Controller = PaddleController::Cpu;
        m_Side = side;
        Setup();
    }

    void SetAsPlayerControlled(const KeyboardScheme& keyScheme, Side side)
    {
        m_Controller = PaddleController::Human;
        m_KeyScheme = keyScheme;
        m_Side = side;
        Setup();
    }
};

bool BallInsidePaddle(Ball& ball, Paddle& paddle)
{
    // AABB 1
    int x1Min = ball.GetPosition().X;
    int x1Max = ball.GetPosition().X + BallWidth;
    int y1Max = ball.GetPosition().Y + BallHeight;
    int y1Min = ball.GetPosition().Y;

    Vector2 pPos = paddle.GetPosition();

    // AABB 2
    int x2Min = pPos.X;
    int x2Max = pPos.X + PaddleWidth;
    int y2Max = pPos.Y + PaddleHeight;
    int y2Min = pPos.Y;

    // Collision tests
    if (x1Max < x2Min || x1Min > x2Max) return false;
    if (y1Max < y2Min || y1Min > y2Max) return false;

    return true;
}

class PongApp : public Application
{
private:
    Renderer2D m_Renderer;
    Renderer2D m_UIRenderer;

    Paddle m_PaddleOne;
    Paddle m_PaddleTwo;
    Ball m_Ball;

public:
    virtual void Initalize()
    {
        Window->SetClearColor(Color::Black);
        MyFont = new Font("Data/font.ttf", 13);

        m_Renderer.Init(Matrix4::Orthographic(Window->Width() / 16.f, 0, 0, Window->Height() / 16.f, 1.0f, -1.0f));
        m_UIRenderer.Init(Matrix4::Orthographic(Window->Width(), 0, 0, Window->Height(), 1.0f, -1.0f));

        m_PaddleOne.SetAsPlayerControlled(PlayerOneKeyboard, Side::Left);
        m_PaddleTwo.SetAsPlayerControlled(PlayerTwoKeyboard, Side::Right);
        m_Ball.Start();
    }

    Timer timer;

    virtual void Update(const GameTime& time)
    {
        KeyboardState state = Keyboard::GetState();
        
        if (state.IsKeyDown(Keys::Escape) && !GameOver)
        {
            if (timer.Running() && timer.ElapsedTimeMs() > 100)
            {
                Paused = !Paused;
                if (!Paused) {
                    timer.Stop();
                }
            }
            timer.Start();
        }

        if (Paused) return;

        if (!GameOver)
        {
            m_Ball.Update(time);
            m_PaddleOne.Update(time, m_Ball);
            m_PaddleTwo.Update(time, m_Ball);
        }

        if (GameOver)
        {
            if (state.IsKeyDown(Keys::Space))
            {
                m_Ball.Start();
                GameOver = false;
            }
        }
    }

    Vector2 MultiplyVector2ByMatrix4(float x, float y, const Matrix4& mat4)
    {
        auto a = mat4.Multiply(Vector3(x, y, 1.0f));
        return { a.X, a.Y };
    }

    virtual void Render()
    {
        m_Renderer.Begin();
        m_PaddleOne.Render(&m_Renderer);
        m_PaddleTwo.Render(&m_Renderer);
        
        if (!GameOver)
        {
            m_Ball.Render(&m_Renderer);
        }
 
        m_Renderer.End();
        m_Renderer.Present();

        m_UIRenderer.Begin();
        
        if (GameOver)
        {
            const String gameOverStr = "Game Over!\nSpace to restart";

            Vector2 strSize = MyFont->MeasureString(gameOverStr);
            Vector2 pos(
                Window->Width() / 2 - strSize.X / 2,
                Window->Height() / 2 - strSize.Y / 2
            );
            m_UIRenderer.DrawString(MyFont, gameOverStr, pos, Color::Red, TextAlignment::Centre);
        }

        if (Paused)
        {
            const String gameOverStr = "Paused...";

            Vector2 strSize = MyFont->MeasureString(gameOverStr);
            Vector2 pos(
                Window->Width() / 2 - strSize.X / 2,
                Window->Height() / 2 - strSize.Y / 2
            );
            m_UIRenderer.DrawString(MyFont, gameOverStr, pos, Color::Red, TextAlignment::Centre);
        }

        m_UIRenderer.End();
        m_UIRenderer.Present();
    }
};

int GeneMain(int argc, char** argv)
{
    Application *app = new PongApp;
    app->Start(800, 600, "Pong");

    return 0;
}