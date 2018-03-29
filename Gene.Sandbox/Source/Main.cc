#include <Platform/Window.h>
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
    
    window->Show();
    while (window->Running())
    {
    	window->PollEvents();
		
		window->SetClearColor(Color::Red);
		window->Clear();

    	window->SwapBuffers();  
    }
    return 0;
}