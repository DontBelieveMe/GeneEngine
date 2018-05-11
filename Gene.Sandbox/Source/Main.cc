#if 1
#include <Platform/Window.h>
#include <Graphics/Color.h>
#include <Graphics/Renderer2D.h>

int GeneMain(int argc, char **argv)
{
    using namespace Gene::Platform;
    using namespace Gene;
    using namespace Gene::Graphics;

    WindowInfo info;
    info.Width = 800;
    info.Height = 600;
    info.Title = "Hello World!";

    Window *window = Window::CreateWindow(info);
    window->Create();
    window->SetClearColor(Color::CornflowerBlue);

    Renderer2D renderer;
    renderer.Init(Matrix4::Orthographic(16.f, 0.f, 0.f, 8.f, 1.0f, -1.0f));

    window->Show();
    while(window->Running()) {
        window->PollEvents();

        window->Clear();
        renderer.Begin();
        renderer.FillCircle({4,4}, 4, Color::Red, 32);
        //renderer.FillRectangle({-0.5f, -0.5f}, 1.0f, 1.f, Color::Green);
        renderer.End();
        renderer.Present();

        window->SwapBuffers();
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

bool IsKeyPressed(const Gene::Input::KeyboardState& state, Gene::Input::Keys key, Gene::Platform::Timer& timer)
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
    using namespace Gene::Platform;
    using namespace Gene::Graphics;
    using namespace Gene;
	using namespace Gene::Input;
	using namespace Gene::Audio;

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
