#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Platform/IWindow.hpp>

#include <Gene2/Core/StdLib/Memory.hpp>
#include <Gene2/Graphics/RenderDevice.hpp>
#include <Gene2/Input/Keys.hpp>
#include <Gene2/Debug/Assert.hpp>

#include <Gene2/Core/StdLib/Random.hpp>
#include <Gene2/Core/Math/Matrix4.hpp>
#include <Gene2/Core/StdLib/Math.hpp>

#include <ctime>

#define TINYOBJLOADER_IMPLEMENTATION
#include <Gene2/Lib/tiny_obj_loader.Lib.hpp>

int main()
{
	g2::Random::Seed((unsigned int) time(0));
	G2_CORE_LOGGER()->AddRoute<g2::ConsoleLoggerRoute>();
	
	g2::SharedPtr<g2::IWindow> window = g2::IWindow::Create(
		g2::WindowConfig(1280, 720, "Gene2 Demo!")
	);
	
	g2::RenderDevice renderDevice;

	renderDevice.SetContextAttribute(g2::CA_GL_MAJOR_VERSION, 3);
	renderDevice.SetContextAttribute(g2::CA_GL_MINOR_VERSION, 3);
	renderDevice.SetContextAttribute(g2::CA_GL_PROFILE, g2::AG_PROFILE_CORE);

	renderDevice.Init(window);
	
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;
	tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, "Assets/Suzanne.obj");

	g2::InputLayoutDef inputLayoutDef;
	inputLayoutDef.DefineAttribute("in_position", 0, g2::VertexAttribInputType::Float3, 0, 0);

	g2::ShaderHandle shader = renderDevice.CreateShader("Assets/Test.shader", inputLayoutDef);

	std::vector<float> vertices;
	for (const tinyobj::shape_t& shape : shapes)
	{
		for (const tinyobj::index_t& index : shape.mesh.indices)
		{
			int vindex = index.vertex_index * 3;
			vertices.push_back(attrib.vertices[vindex + 0]);
			vertices.push_back(attrib.vertices[vindex + 1]);
			vertices.push_back(attrib.vertices[vindex + 2]);
		}
	}

	g2::BufferHandle vertexBuffer = renderDevice.CreateBuffer(g2::BF_VERTEX_BUFFER,
		g2::MemoryRef(vertices.data(),vertices.size()*sizeof(float))
	);

	g2::Matrix4 projection = g2::Matrix4::MakePerspective((float)window->GetWidth() / window->GetHeight(), 90.f, 100.f, 0.1f);
	g2::UniformHandle projectionUniform = renderDevice.CreateUniform(shader, "u_projection", g2::UNIFORM_TYPE_MAT4);

	g2::UniformHandle transformUniform = renderDevice.CreateUniform(shader, "u_transform", g2::UNIFORM_TYPE_MAT4);

	window->Show();

	g2::Color clearColor = g2::Color::Red;
	renderDevice.SetClearColor(clearColor);

	float theta = 0;
	float thx = 0;
	while (window->IsOpen())
	{
		g2::Event event;
		while (window->PollEvent(event))
		{
			switch (event.EventType)
			{
			case g2::EVENT_KEYDOWN:
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

		renderDevice.SetUniformValue(projectionUniform, projection.Elements);

		g2::Matrix4 transform = g2::Matrix4::MakeRotationY(theta) * g2::Matrix4::MakeRotationX(theta) * g2::Matrix4::MakeTranslation({ 0,0,-2 });

		theta += 0.1f;
		theta = g2::Math::Wrap(theta, 0.f, 360.f);

		renderDevice.SetUniformValue(transformUniform, transform.Elements);

		renderDevice.SetVertexBuffer(0, vertexBuffer, 3 * sizeof(float), 0);
		renderDevice.DrawPrimitive(shader, vertices.size());

		renderDevice.SwapBuffers();
	}

    return 0;
}
