#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Platform/IWindow.hpp>

int main()
{
	G2_CORE_LOGGER()->AddRoute<g2::ConsoleLoggerRoute>();
	
	g2::IWindow* window = g2::IWindow::Create(g2::WindowConfig(800, 600, "Gene2 Demo!"));
	window->Show();
	
	while (window->IsOpen())
	{
		window->PollEvents();
	}

    return 0;
}