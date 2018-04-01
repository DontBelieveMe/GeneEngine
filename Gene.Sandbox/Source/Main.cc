#include <Platform/Window.h>
#include <Graphics/Renderer2D.h>
#include <Graphics/Color.h>

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
	window->SetClearColor(Color::Red);
    
    Renderer2D renderer;
    renderer.Init(Matrix4::Orthographic(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f));

    window->Show();
    while (window->Running())
    {
    	window->PollEvents();
		
		window->Clear();

        renderer.Begin();
        renderer.FillRectangle({ -0.5f, -0.5f }, 1.0f, 1.0f, Color::Red);
        renderer.End();
        renderer.Present();

    	window->SwapBuffers();  
    }
    return 0;
}