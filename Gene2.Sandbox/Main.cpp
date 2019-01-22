#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Platform/IWindow.hpp>

#include <Gene2/Core/StdLib/Memory.hpp>
#include <Gene2/Graphics/RenderDevice.hpp>
#include <Gene2/Input/Keys.hpp>

int main()
{
	G2_CORE_LOGGER()->AddRoute<g2::ConsoleLoggerRoute>();
	
	g2::SharedPtr<g2::IWindow> window = g2::IWindow::Create(
		g2::WindowConfig(800, 600, "Gene2 Demo!")
	);
	
	g2::RenderDevice renderDevice;
	renderDevice.Init(window);

	window->Show();
	
	while (window->IsOpen())
	{
		g2::Event event;
		while (window->PollEvent(event))
		{
			switch (event.EventType)
			{
			case g2::EVENT_MOUSEUP:
			{
				G2_TRACE("Mouse Button Up := {0}", event.Mouse.Button);
				break;
			}
			case g2::EVENT_MOUSEDOWN:
			{
				G2_TRACE("Mouse Button Down := {0}", event.Mouse.Button);
				break;
			}
			case g2::EVENT_QUIT:
			{
				window->Close();
				break;
			}
			case g2::EVENT_KEYDOWN:
			{
				G2_TRACE("KEYDOWN := Shift: {0}, Ctrl: {1}, Alt {2} | Char {3}",
					(event.Key.Modifiers & g2::KMOD_SHIFT) != 0,
					(event.Key.Modifiers & g2::KMOD_CTRL) != 0,
					(event.Key.Modifiers & g2::KMOD_ALT) != 0,
					event.Key.Key
				);
				break;
			}
			case g2::EVENT_KEYUP:
			{
				G2_TRACE("KEYUP := Shift: {0}, Ctrl: {1}, Alt {2} | Char {3}",
					(event.Key.Modifiers & g2::KMOD_SHIFT) != 0,
					(event.Key.Modifiers & g2::KMOD_CTRL) != 0,
					(event.Key.Modifiers & g2::KMOD_ALT) != 0,
					event.Key.Key
				);
				break;
			}
			}
		}
	}

    return 0;
}