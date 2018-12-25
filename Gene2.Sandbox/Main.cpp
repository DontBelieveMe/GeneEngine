#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Platform/IWindow.hpp>

#include <Gene2/Core/StdLib/Memory.hpp>

#include <Gene2/Input/Keys.hpp>

int main()
{
	G2_CORE_LOGGER()->AddRoute<g2::ConsoleLoggerRoute>();
	
	g2::SharedPtr<g2::IWindow> window = g2::IWindow::Create(
		g2::WindowConfig(800, 600, "Gene2 Demo!")
	);
	
	window->Show();
	
	while (window->IsOpen())
	{
		g2::Event evt;
		while (window->PollEvent(evt))
		{
			switch (evt.EventType)
			{
			case g2::EVENT_QUIT:
				window->Close();
				break;
			}
		}
	}

    return 0;
}