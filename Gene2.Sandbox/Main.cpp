#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Platform/IWindow.hpp>

#include <Gene2/Core/StdLib/Memory.hpp>
#include <Gene2/Graphics/RenderDevice.hpp>
#include <Gene2/Input/Keys.hpp>
#include <Gene2/Debug/Assert.hpp>

#include <Gene2/Core/StdLib/Random.hpp>

#include <ctime>

int main()
{
	g2::Random::Seed((unsigned int) time(0));
	G2_CORE_LOGGER()->AddRoute<g2::ConsoleLoggerRoute>();
	
	g2::SharedPtr<g2::IWindow> window = g2::IWindow::Create(
		g2::WindowConfig(800, 600, "Gene2 Demo!")
	);
	
	g2::RenderDevice renderDevice;

	renderDevice.SetContextAttribute(g2::CA_GL_MAJOR_VERSION, 3);
	renderDevice.SetContextAttribute(g2::CA_GL_MINOR_VERSION, 3);
	renderDevice.SetContextAttribute(g2::CA_GL_PROFILE, g2::AG_PROFILE_CORE);

	renderDevice.Init(window);
	
	float vertices[] = {
		-0.5f, -0.5f, 0.f,     0.75f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.f,      0.0f, 0.75f, 0.0f,
		0.0f, 0.5f, 0.0f,      0.0f, 1.0f, 0.75f
	};

	g2::InputLayoutDef inputLayoutDef;
	inputLayoutDef.DefineAttribute("in_position", 0, g2::VertexAttribInputType::Float3);
	inputLayoutDef.DefineAttribute("in_color", 1, g2::VertexAttribInputType::Float3);

	g2::ShaderHandle shader = renderDevice.CreateShader("Assets/Test.shader", inputLayoutDef);
	g2::BufferHandle vertexBuffer = renderDevice.CreateBuffer(g2::BF_VERTEX_BUFFER, g2::MemoryRef(vertices, sizeof(vertices)));

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
			case g2::EVENT_MOUSEDOWN:
			{
				const float r = g2::Random::FloatRange(0.0f, 1.0f);
				const float g = g2::Random::FloatRange(0.0f, 1.0f);
				const float b = g2::Random::FloatRange(0.0f, 1.0f);

				clearColor = g2::Color(r, g, b, 1.0f);
				renderDevice.SetClearColor(clearColor);
				break;
			}
			case g2::EVENT_QUIT:
			{
				window->Close();
				break;
			}
			}
		}

		renderDevice.Clear(g2::CF_CLEAR_COLOR_BUFFER | g2::CF_CLEAR_DEPTH_BUFFER);

		renderDevice.DrawPrimitive(shader, vertexBuffer, 1);

		renderDevice.SwapBuffers();
	}

    return 0;
}
