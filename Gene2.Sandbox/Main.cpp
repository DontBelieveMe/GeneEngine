#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Platform/IWindow.hpp>

#include <Gene2/Core/StdLib/Memory.hpp>
#include <Gene2/Graphics/RenderDevice.hpp>
#include <Gene2/Input/Keys.hpp>
#include <Gene2/Debug/Assert.hpp>
#include <Gene2/Graphics/ForwardRenderer3D.hpp>

#include <Gene2/Core/StdLib/Random.hpp>

#include <ctime>

int main()
{
	g2::Random::Seed(time(0));
	G2_CORE_LOGGER()->AddRoute<g2::ConsoleLoggerRoute>();
	
	g2::SharedPtr<g2::IWindow> window = g2::IWindow::Create(
		g2::WindowConfig(800, 600, "Gene2 Demo!")
	);
	
	g2::RenderDevice renderDevice;
	renderDevice.Init(window);
	
	float vertices[] = {
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.0f, 0.5f, 0.0f
	};

	
	g2::InputLayoutDef inputLayoutDef;
	inputLayoutDef.DefineAttribute("in_position", 0, g2::VertexAttribInputType::Float3);

	g2::ShaderHandle shader = renderDevice.CreateShader("Assets/Test.shader", inputLayoutDef);
	g2::BufferArrayHandle bufferArray = renderDevice.CreateBufferArray(shader);
	g2::BufferHandle vertexBuffer = renderDevice.CreateBuffer(g2::BF_VERTEX_BUFFER, g2::MemoryRef(vertices, sizeof(vertices)), bufferArray);

	g2::ForwardRenderer3D renderer;

	window->Show();

	g2::Color clearColor = g2::Color::Red;
	renderDevice.SetClearColor(clearColor);


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
				clearColor = g2::Color(g2::Random::FloatRange(0.0f, 1.0f), g2::Random::FloatRange(0.0f, 1.0f), g2::Random::FloatRange(0.0f, 1.0f), 1.0f);
				renderDevice.SetClearColor(clearColor);
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

				const int kRate = 5;
				
				switch (event.Key.Key)
				{
				case g2::K_r:
					clearColor = g2::Color(clearColor.GetRed() + kRate, clearColor.GetGreen(), clearColor.GetBlue(), 255);
					renderDevice.SetClearColor(clearColor);
					break;
				case g2::K_g:
					clearColor = g2::Color(clearColor.GetRed(), clearColor.GetGreen() + kRate, clearColor.GetBlue(), 255);
					renderDevice.SetClearColor(clearColor);
					break;
				case g2::K_b:
					clearColor = g2::Color(clearColor.GetRed(), clearColor.GetGreen(), clearColor.GetBlue() + kRate, 255);
					renderDevice.SetClearColor(clearColor);
					break;

				}
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

		renderDevice.Clear(g2::CF_CLEAR_COLOR_BUFFER | g2::CF_CLEAR_DEPTH_BUFFER);

		renderer.Render(&renderDevice, bufferArray, shader);

		renderDevice.SwapBuffers();
	}

    return 0;
}
