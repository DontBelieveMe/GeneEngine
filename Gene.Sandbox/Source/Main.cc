#include <Platform/Window.h>
#include <Graphics/GLSLShader.h>
#include <Math/Vector3.h>
#include <Graphics/Color.h>
#include <IO/File.h>
#include <Graphics/Buffer.h>
#include <Platform/OpenGL.h>
#include <Graphics/VertexArray.h>
#include <Math/Math.h>
#include <math.h>
#include <Input/Mouse.h>

static void CreateTriangle(Gene::Graphics::VertexArray& vao)
{
	GLfloat vertices[] = {
		// Positions         // Colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Top 
	};

	Gene::Graphics::Buffer *vbo = new Gene::Graphics::Buffer(Gene::Graphics::Buffer::Type::ArrayBuffer);

	Gene::Graphics::BufferDescriptor dsc;
	dsc.Data = vertices;
	dsc.DataType = Gene::OpenGL::GLType::Float;
	dsc.Size = sizeof(vertices);
	dsc.DrawType = Gene::Graphics::BufferDrawType::Static;
	vbo->SetData(dsc);

	#pragma region Attributes
	Gene::Graphics::AttributeDescriptor vertexAttrib;
	vertexAttrib.ByteOfffset = 0;
	vertexAttrib.ComponentCount = 3;
	vertexAttrib.Index = 0;

	Gene::Graphics::AttributeDescriptor colorAttrib;
	colorAttrib.ByteOfffset = 3 * sizeof(GLfloat);
	colorAttrib.ComponentCount = 3;
	colorAttrib.Index = 1;
	#pragma endregion

	vao.RegisterAttribute(vbo, vertexAttrib);
	vao.RegisterAttribute(vbo, colorAttrib);
}

int main()
{
	using namespace Gene::Platform;
	using namespace Gene::Graphics;
	using namespace Gene::Math;
	using namespace Gene::IO;
	using namespace Gene::Input;

	Window *window = Window::CreateWindow({ 800, 600, "Hello World!" });
	window->Create();
	window->CreateGLContext();
	
	GLSLShader shader;
	shader.CompileFromFiles("Data/vertex.glsl", "Data/fragment.glsl");
	shader.Enable();

	window->SetClearColor(Color::CornflowerBlue);

	VertexArray vao;
	CreateTriangle(vao);

	window->Show();
	while (window->Running())
	{
		window->Update();
		MouseState state = Mouse::GetState();
		printf("%f %f\n", state.Position.X, state.Position.Y);

		vao.DebugDraw();
		window->SwapBuffers();
	}

	return 0;
}