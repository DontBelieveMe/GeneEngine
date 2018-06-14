#if 1
#include <Platform/Window.h>
#include <Graphics/Color.h>
#include <Graphics/Renderer2D.h>
#include <Platform/Time.h>
#include <Input/Mouse.h>
#include <Math/Math.h>

int GeneMain(int argc, char **argv)
{
    using namespace gene::platform;
    using namespace gene;
    using namespace gene::graphics;
    using namespace gene::input;

    WindowInfo info;
    info.Width = 800;
    info.Height = 600;
    info.Title = "Hello World!";

    Window *window = Window::CreateWindow(info);
    window->Create();
    window->SetClearColor(Color(69, 76, 86, 255));

    GameTime time;
    time.Start();

    Renderer2D renderer;
    renderer.Init(Matrix4::Orthographic(window->Width(), 0.f, 0.f, window->Height(), 1.0f, -1.0f));

    float x = 75.0f;
    float y = 75.0f;
    Vector2 ballPosition;
    
    InputController *input = window->GetInputController();  
    MouseDevice *mouseDevice = input->GetMouseDevice();

    window->Show();
    while(window->Running()) {
        time.StartFrame();
        window->PollEvents();
        
        MouseState state = Mouse::GetState();
        if (mouseDevice->IsButtonDown(MouseDevice::Button::Left)) {
            Vector2i mPos = mouseDevice->GetCursorPosition();
            LOG(LogLevel::Debug, "X: ", mPos.X, ", Y: ", mPos.Y);
            Vector2 diff(mPos.X - x, mPos.Y - y);
            diff.Normalize();
			
            x += diff.X * 10.f;
            y += diff.Y * 10.f;
        }

        window->Clear();
        renderer.Begin();

        renderer.FillCircle({x,y}, 50, Color::Red, 32);
        
        renderer.End();
        renderer.Present();

        if (x-50 > window->Width()) 
        {
            x = -50;
        }

        window->SwapBuffers();
        time.EndFrame();
        time.Sleep(1000.f / 60.f);
    }

    return 0;
}

#endif

#if 0

#include <Platform/Window.h>
#include <Graphics/Renderer2D.h>
#include <Graphics/Color.h>
#include <Runtime/Resources.h>
#include <Input/Keyboard.h>
#include <Platform/Time.h>
#include <Input/Mouse.h>
#include <Audio/WaveFile.h>
#include <Audio/AudioSystem.h>

#include <AL/al.h>
#include <AL/alc.h>

bool IsKeyPressed(const gene::input::KeyboardState& state, gene::input::Keys key, gene::platform::Timer& timer)
{
    if (state.IsKeyDown(key)) {
        if (timer.Running())
        {
            return false;
        }
        else {
            timer.Start();
            return true;
        }
    }
    else {
        timer.Stop();
        return false;
    }
}

int GeneMain(int argc, char **argv)
{
    using namespace gene::platform;
    using namespace gene::graphics;
    using namespace gene;
	using namespace gene::input;
	using namespace gene::audio;

    WindowInfo info;
    info.Width = 600;
    info.Height = 600;
    info.Title = "Hello from GeneEngine.Sandbox";
    info.Borderless = false;

    Window *window = Window::CreateWindow(info);
    
    window->Create();
	window->SetClearColor(Color::CornflowerBlue);

	ResourceManager manager;

	ResourceHandle<WaveFile> wavFile = manager.LoadAsset<WaveFile>(2, "Data/cartoon001.wav");
	wavFile->Loop(true);

    ResourceHandle<Font> uiFont = manager.LoadAsset<Font>(3, "Data/Fonts/Gidole-Regular.ttf");

    window->Show();
	
    Timer debugKeyTimer;

	GameTime gameTimer;
	gameTimer.Init();

    Renderer2D renderer;
    renderer.Init(Matrix4::Orthographic(160, 0, 0, 160, 1.0f, -1.0f));

    Renderer2D uiRenderer;
    uiRenderer.Init(Matrix4::Orthographic(window->Width(), 0, 0, window->Height(), 1.0f, -1.0f));

    unsigned int points = 32;
    float radius = 15;
    Vector2 circlePos(160.f / 2, 160.f / 2);

    while (window->Running())
    {
        window->PollEvents();
        gameTimer.StartFrame();

        window->Clear();
        renderer.Begin();
        
        renderer.FillCircle(circlePos, radius, Color::Red, points);

        renderer.FillRectangle({ 40, 40 }, 10, 10, Color::Black);
        renderer.FillRectangle({ 50, 50 }, 10, 10, Color::Blue);
        renderer.End();

        uiRenderer.Begin();
        uiRenderer.DrawString(uiFont, "Hello World!", { 50, 50 }, Color::Green);
        //uiRenderer.DrawTexture({0,0},uiFont->GLTexture());
        uiRenderer.End();

        renderer.Present();
        uiRenderer.Present();

        window->SwapBuffers();

		gameTimer.EndFrame();

        gameTimer.Sleep(1000.0f / 60.0f);
    }
	
	manager.DestroyAll();

    return 0;
}
#endif
