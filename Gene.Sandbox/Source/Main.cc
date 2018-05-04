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
	window->SetClearColor(Color::Green);
    
    Renderer2D renderer;
    renderer.Init(Matrix4::Orthographic(160, 0, 0, 160, 1.0f, -1.0f));

	ResourceManager manager;
	
	TextureParameters params;
	params.Filtering = FilteringOptions::Nearest;

	ResourceHandle<Texture2D> texture = manager.LoadAsset<Texture2D>(1, "Data/spr_test_0.png", params);
	
	AudioSystem audioManager;
	audioManager.Init();

	ResourceHandle<WaveFile> wavFile = manager.LoadAsset<WaveFile>(2, "Data/cartoon001.wav");
	wavFile->Loop(true);

    window->Show();
	
    Timer debugKeyTimer;
    bool bDebugMode = false;

	GameTime gameTimer;
	gameTimer.Init();
    
    // Todo look into enabling multisampling.
    //glEnable(GL_MULTISAMPLE);

    int points = 32;

    Vector2 pos = { 1,1 };
    while (window->Running())
    {
        window->PollEvents();
		
        KeyboardState keyState = Keyboard::GetState();
        MouseState mouseState = Mouse::GetState();

        if (IsKeyPressed(keyState, Keys::F11, debugKeyTimer))
        {
            bDebugMode = !bDebugMode;

            if (bDebugMode)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        if (mouseState.IsButtonDown(MouseButton::Left) && !wavFile->IsPlaying()) {
            audioManager.PlayWav(wavFile);
        }

        if (keyState.IsKeyDown(Keys::L))
            {
                points += 1;
            }
            if (keyState.IsKeyDown(Keys::K) && points > 3)
            {
                points -= 1;
            }
        

        if (mouseState.IsButtonDown(MouseButton::Right)) {
            Vector2i mousePosition = mouseState.GetPosition();
            mousePosition.X /= 3.75;
            mousePosition.Y /= 3.75f;
            Vector2 diff = Vector2(mousePosition.X, mousePosition.Y) - pos;
            diff.Normalize();
            pos += diff * 0.05f * gameTimer.DeltaInMilliSeconds();
        }
        if (keyState.IsKeyDown(Keys::RightArrow)) {
            pos.X += 0.05f * gameTimer.DeltaInMilliSeconds();
        }
        else if (keyState.IsKeyDown(Keys::LeftArrow)) {
            pos.X -= 0.05f * gameTimer.DeltaInMilliSeconds();
        }
        
        gameTimer.StartFrame();

        renderer.Begin();
        
        renderer.FillCircle({ 22.5,22.5 }, 20, Color::Red, points);

        renderer.FillRectangle({ 40, 40 }, 10, 10, Color::Black);
        renderer.FillRectangle({ 50, 50 }, 10, 10, Color::Blue);

        renderer.End();
        renderer.Present();

    	window->SwapBuffers();  

		gameTimer.EndFrame();

        gameTimer.Sleep(1000.0f / 60.0f);
    }
	
	manager.DestroyAll();

    return 0;
}