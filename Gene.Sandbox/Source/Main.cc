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
#include <memory>
#include <Graphics/Texture2D.h>

static void CreateTriangle(Gene::Graphics::VertexArray& vao, Gene::Graphics::Buffer** ebo)
{
	using namespace Gene::Platform;
	using namespace Gene::Graphics;
	using namespace Gene::Math;
	using namespace Gene::IO;
	using namespace Gene::Input;
	
	GLfloat vertices[] = {
		0.5f,   0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// Top Right
		0.5f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// Bottom Right
	   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// Bottom Left
	   -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f// Top Left 
	};	

	*ebo = new Buffer(Buffer::Type::ElementBuffer);
	std::shared_ptr<Buffer> vbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
	vao.Enable();
	BufferDescriptor dsc;
	dsc.Data = vertices;
	dsc.DataType = Gene::OpenGL::GLType::Float;
	dsc.Size = sizeof(vertices);
	dsc.DrawType = BufferDrawType::Static;
	vbo->SetData(dsc);
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};  


	BufferDescriptor desc;
	desc.Data = indices;
	desc.DataType = Gene::OpenGL::GLType::UnsignedInt;
	desc.Size = sizeof(indices);
	desc.DrawType = BufferDrawType::Static;

	(*ebo)->SetData(desc);

	#pragma region Attributes
	AttributeDescriptor vertexAttrib;
	vertexAttrib.ByteOfffset = 0;
	vertexAttrib.ComponentCount = 3;
	vertexAttrib.Index = 0;
	vertexAttrib.Stride = 6 * sizeof(GLfloat);

	AttributeDescriptor colorAttrib;
	colorAttrib.ByteOfffset = 3 * sizeof(GLfloat);
	colorAttrib.ComponentCount = 3;
	colorAttrib.Index = 1;
	colorAttrib.Stride = 6 * sizeof(GLfloat);
	#pragma endregion

	vao.RegisterAttribute(vbo.get(), vertexAttrib);
	vao.RegisterAttribute(vbo.get(), colorAttrib);
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

	window->SetClearColor(Color::Black);

	Buffer *ebo;
	VertexArray vao;
	CreateTriangle(vao, &ebo);


	window->Show();
	while (window->Running())
	{
		window->PollEvents();

		vao.DebugDrawElements(ebo);
		window->SwapBuffers();
	}

	return 0;
}