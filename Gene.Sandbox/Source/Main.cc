#include <Platform/Window.h>
#include <Graphics/Renderer2D.h>
#include <Graphics/Color.h>
#include <Runtime/Resources.h>
#include <Input/Keyboard.h>
#include <Platform/Time.h>

#include <Audio/WaveFile.h>
#include <Audio/AudioSystem.h>

#include <AL/al.h>
#include <AL/alc.h>

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
	
	GameTime time;
	time.Init();

    Vector2 pos = { 1,1 };
    while (window->Running())
    {
        window->PollEvents();
		
        KeyboardState keyState = Keyboard::GetState();
        if (keyState.IsKeyDown(Keys::D)) {
            pos.X += 0.05f * time.DeltaInMilliSeconds();
        }
        else if (keyState.IsKeyDown(Keys::A)) {
            pos.X -= 0.05f * time.DeltaInMilliSeconds();
        }
        
        time.StartFrame();

        renderer.Begin();
        
        renderer.DrawTexture(pos, texture);
        renderer.End();
        renderer.Present();

    	window->SwapBuffers();  

		time.EndFrame();

        time.Sleep(1000.0f / 60.0f);
    }
	
	manager.DestroyAll();

    return 0;
}