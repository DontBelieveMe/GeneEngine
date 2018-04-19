#include <Platform/Window.h>
#include <Platform/Time.h>

#include <Input/Keyboard.h>

#include <Graphics/Font.h>
#include <Graphics/Renderer2D.h>

#include <Audio/AudioSystem.h>
#include <Runtime/Resources.h>

using namespace Gene;
using namespace Gene::Platform;
using namespace Gene::Graphics;
using namespace Gene::Input;
using namespace Gene::Audio;

/*
  [] We need some a camera:                                                                 ]   
  [] Camera shake: angle = maxAngle * shake * GetRandomFloatNegOneToOne();                  |
                   offsetX = maxOffset * shake * GetRandomFloatNegOneToOne();               |
                   offsetY = maxOffset * shake * GetRandomFloatNegOneToOne();                > This is now kindof implemented in the pong demo.
                                                                                            |
                   ShakeyCamera.angle = NormalCamera.angle + angle;                         |
                   ShakeyCamera.center = NormalCamera.center + Vec2(offsetX, offsetY);      |
  [] Or maybe perlin noise or something? https://www.youtube.com/watch?v=tu-Qe66AvtY        ]
  [] Some collision base code
    [] Simple AABB intersection
    [] Actual collision response
  [] Utility code for randomness
  [] Maybe integrate the Application base framework as part of the lib?
  [] Layer support would be cool (e.g game render layer, UI render layer)
  [] Maybe some UI utilities
    [] Center position on screen
    [] Rotate text
    [] Change font size dynamically? (involve regenerating texture)
  [] Input utilities
    [] IsKeyPressed for typing or single presses - e.g for activating menus or interacting w/ objects
  [] Math utilities 
    [] Vector2 -> +,-,*,/,+=,/=,*=,-= operators
    [] Static Matrix4 operations
      [] e.g. Matrix4::Scale()
      [] consistant Matrix4::operator* overloading
      [] Make matrices immutable

  [] NOT nessersary, but cool to have
    [] VFS for resource loading
      [] Would allow for load from disk or embedding in exe
      [] Cool way to abstract away platform FS issues
  [] Lighting
    [] Can add lights to the scene
      [] Change color, radius, intensity etc...
    [] Positional audio
      [] Technically the support is there we just need to abstract it into an API
    [] Tiled map loading
      [] A simple version of this would be good for LD
        [] More advanced features like object integration,
        [] Audio integration (Set audio `areas`)
        [] etc...
*/

float Random(float min, float max) //range : [min, max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    const float range = fabs(min - max);
    float random = range * ((((float)rand()) / (float)RAND_MAX)) + min;
    return random;
}

class Camera {
private:
    float m_Shake;
    float m_ShakeMaxAngle;
    float m_ShakeMaxOffset;
    
    Timer m_Timer;
    float m_ShakeTime;
    bool m_IsShaking;

    Matrix4 GetRotation()
    {
        Matrix4 rotation;
        rotation.RotateZ(Angle);

        return rotation;
    }

public:
    Camera() :
        m_Shake(0), m_ShakeMaxAngle(0), m_ShakeMaxOffset(0), m_IsShaking(false), m_ShakeTime(0), Angle(0) {}

    Matrix4 GetViewMatrix()
    {
        Matrix4 translate;
        translate.Translate(Position);

        Matrix4 rotation = GetRotation();

        return translate.Multiply(rotation);
    }

    void Shake(float shake, float maxAngle, float maxOffset, float time)
    {
        m_Shake = shake;
        m_ShakeMaxAngle = maxAngle;
        m_ShakeMaxOffset = maxOffset;
        m_IsShaking = true;
        m_ShakeTime = time;
        m_Timer.Start();
    }

    void Update()
    {
        if (m_IsShaking)
        {
            if (m_Timer.ElapsedTimeMs() < m_ShakeTime)
            {
                float angle = m_ShakeMaxAngle * m_Shake * Random(-1.0f, 1.0f);

                float offsetX = m_ShakeMaxOffset * m_Shake * Random(-1.0f, 1.0f);
                float offsetY = m_ShakeMaxOffset * m_Shake * Random(-1.0f, 1.0f);
                Angle = angle;
                Position = Vector2(offsetX, offsetY);
            }
            else {
                m_IsShaking = false;
                m_Timer.Stop();
                m_Shake = 0;
                m_ShakeMaxAngle = 0;
                m_ShakeTime = 0;
                m_ShakeMaxOffset = 0;
                Angle = 0;
                Position.Set(0);
            }
        }

    }

    Vector2 Position;
    float Angle;
};

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

static Camera *MyCamera;

static AudioSystem *AudioPlayer;

enum class PaddleController
{
    Cpu, Human
};

enum class Side  
{
    Left, Right
};

class Ball {
private:
    Vector2 m_Position;
    Vector2 m_Velocity;

public:
    void Start() {
        m_Position.X = (AreaWidth / 2) - (BallWidth / 2);
        m_Position.Y = (AreaHeight / 2) - (BallHeight / 2);

        m_Velocity.X = BallSpeedRange;
        m_Velocity.Y = BallSpeedRange;
    }

    void Update(const GameTime& time) {
        if (m_Position.X + BallWidth > AreaWidth || m_Position.X < 0) GameOver = true;
        if (m_Position.Y + BallHeight > AreaHeight || m_Position.Y < 0) m_Velocity.Y = -m_Velocity.Y;

        if (GameOver)
        {
            m_Velocity.Set(0);

            m_Position.X = (AreaWidth / 2) - (BallWidth / 2);
            m_Position.Y = (AreaHeight / 2) - (BallHeight / 2);
        }

        m_Position += m_Velocity * time.DeltaInMilliSeconds();
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

class Paddle {
private:
    PaddleController m_Controller;
    KeyboardScheme m_KeyScheme;
    Side m_Side;

    Vector2 m_Position;
    Vector2 m_Velocity;

    bool m_IsKicking = false;
    Timer m_KickTimer;

    float m_XPosConst;

    void KickBack()
    {
        m_IsKicking = true;
        m_KickTimer.Start();
    }

    void CheckWallColliders()
    {
        const float yWallOffset = 0.5f;

        if (m_Position.Y + PaddleHeight > AreaHeight - yWallOffset) 
            m_Position.Y = AreaHeight - PaddleHeight - yWallOffset;

        if (m_Position.Y < yWallOffset)
            m_Position.Y = yWallOffset;
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
            ResourceHandle<WaveFile> hitSound = ResourceManager::Get()->GetAsset<WaveFile>(0);
            AudioPlayer->PlayWav(hitSound);

            Vector2 bVel = ball.GetVelocity();
            Vector2 newVel(-bVel.X, bVel.Y);
            ball.SetVelocity(newVel);

            MyCamera->Shake(0.5f, 1.5f, 0.01f, 250.f);
            KickBack();
        }

        m_Position += m_Velocity * time.DeltaInMilliSeconds();

        CheckWallColliders();

        if (m_IsKicking)
        {
            if (m_KickTimer.ElapsedTimeMs() < 250)
            {
                float max, min;
                switch (m_Side) {
                case Side::Left:
                    max = 0;
                    min = -1.0f;
                    break;
                case Side::Right:
                    max = 1.0f;
                    min = 0.f;
                    break;
                }
               // m_Position.X = m_XPosConst + (1.5f * 1.5f * Random(min, max));
            }
            else {
                m_IsKicking = false;
                m_KickTimer.Stop();
                m_Position.X = m_XPosConst;
            }
        }
    }

    void Setup()
    {
        int offsetFromWall = 3;
        switch (m_Side)
        {
        case Side::Left:
            m_Position = Vector2(offsetFromWall, 1);
            break;
        case Side::Right:
            m_Position = Vector2(AreaWidth - (offsetFromWall + PaddleWidth), 1);
            break;
        }

        m_XPosConst = m_Position.X;
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
    Vector2 ballPos = ball.GetPosition();
    Vector2 pPos = paddle.GetPosition();

    int x1Min = ballPos.X;
    int x1Max = ballPos.X + BallWidth;
    int y1Max = ballPos.Y + BallHeight;
    int y1Min = ballPos.Y;

    int x2Min = pPos.X;
    int x2Max = pPos.X + PaddleWidth;
    int y2Max = pPos.Y + PaddleHeight;
    int y2Min = pPos.Y;

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

    AudioSystem m_AudioSystem;
    ResourceManager m_ResourceSystem;

    Camera m_Camera;
    
public:
    virtual void Initalize()
    {
        Window->SetClearColor(Color::Black);
        MyFont = new Font("Data/font.ttf", 13);
        MyCamera = &m_Camera;
        m_AudioSystem.Init();
        AudioPlayer = &m_AudioSystem;
        m_ResourceSystem.SetStaticInstance(&m_ResourceSystem);
        
        m_ResourceSystem.LoadAsset<WaveFile>(0, "Data/hit.wav");

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
        m_Camera.Update();

        if (state.IsKeyDown(Keys::U))
        {
            MyCamera->Angle++;
        }

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
        m_Renderer.SetViewMatrix(m_Camera.GetViewMatrix()); 
        m_Renderer.Begin();
        m_Renderer.FillRectangle({ 0, 0 }, AreaWidth, AreaHeight, Color(37, 42, 51, 255));
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