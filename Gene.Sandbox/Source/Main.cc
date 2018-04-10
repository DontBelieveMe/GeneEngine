#include <Platform/Window.h>
#include <Graphics/Renderer2D.h>
#include <Graphics/Color.h>
#include <Runtime/Resources.h>

int GeneMain(int argc, char **argv)
{
    using namespace Gene::Platform;
    using namespace Gene::Graphics;
    using namespace Gene;
    
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

#define DOUGHNUT_TEXTURE 0x01

	ResourceHandle<Texture2D> handle = manager.LoadAsset<Texture2D>(DOUGHNUT_TEXTURE, "Data/spr_test_0.png");
	
    window->Show();
    while (window->Running())
    {
    	window->PollEvents();
		
		window->Clear();

        renderer.Begin();
		renderer.DrawTexture({ 10, 10 }, handle);
        renderer.End();
        renderer.Present();

    	window->SwapBuffers();  
    }
    return 0;
}