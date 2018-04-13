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
    info.Width = 800;
    info.Height = 600;
    info.Title = "Hello from GeneEngine.Sandbox";
    info.Borderless = false;

    Window *window = Window::CreateWindow(info);
    
    window->Create();
	window->SetClearColor(Color::Green);
    
    Renderer2D renderer;
    renderer.Init(Matrix4::Orthographic(window->Width(), 0, 0, window->Height(), 1.0f, -1.0f));

	ResourceManager manager;
	ResourceManager::SetStaticInstance(&manager);

	TextureParameters params;
	params.Filtering = FilteringOptions::Nearest;

	ResourceHandle<Texture2D> texture = manager.LoadAsset<Texture2D>(1, "Data/spr_test_0.png", params);
	
	AudioSystem audioManager;
	audioManager.Init();

	ResourceHandle<WaveFile> wavFile = manager.LoadAsset<WaveFile>(2, "Data/cartoon001.wav");
	audioManager.PlayWav(wavFile);

    window->Show();
	float x = 10;
	GameTime time;
	time.Init();
    while (window->Running())
    {
		time.StartFrame();

		KeyboardState state = Keyboard::GetState();
		if (state.IsKeyDown(Keys::D)) {
			x += 0.05f * time.DeltaInMilliSeconds();
		}
		else if (state.IsKeyDown(Keys::A)) {
			x -= 0.05f * time.DeltaInMilliSeconds();
		}

    	window->PollEvents();
		window->Clear();

        renderer.Begin();
		{
			Matrix4 mat4;
			mat4.Scale(Vector3(8, 8, 1));
			renderer.PushTransform(mat4);
			{
				renderer.DrawTexture({ x, 10 }, texture);
			}
			renderer.PopTransform();
		}
		renderer.End();
		renderer.Present();

    	window->SwapBuffers();  

		time.EndFrame();
		time.Sleep(1000 / 60.f);
    }
    return 0;
}