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
#include <Input/Keyboard.h>
#include <memory>
#include <Graphics/Texture2D.h>

static void CreateTriangle(Gene::Graphics::VertexArray& vao, Gene::Graphics::Buffer** ebo)
{
	using namespace Gene::Graphics;

	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f 
	};	

	GLuint indices[] = { 
		0, 1, 3,  
		1, 2, 3 
	};  
	
	std::shared_ptr<Buffer> vbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
	
	vao.Enable();
	
	BufferDescriptor vertexBufferDesc;
	vertexBufferDesc.Data     = vertices;
	vertexBufferDesc.DataType = Gene::OpenGL::GLType::Float;
	vertexBufferDesc.Size     = sizeof(vertices);
	vertexBufferDesc.DrawType = BufferDrawType::Static;
	vbo->SetData(vertexBufferDesc);

	(*ebo) = new Buffer(Buffer::Type::ElementBuffer);
	
	BufferDescriptor indexBufferDesc;
	indexBufferDesc.Data	  = indices;
	indexBufferDesc.DataType  = Gene::OpenGL::GLType::UnsignedInt;
	indexBufferDesc.Size      = sizeof(indices);
	indexBufferDesc.DrawType  = BufferDrawType::Static;
	(*ebo)->SetData(indexBufferDesc);

	#pragma region Attributes

	AttributeDescriptor vertexAttrib, colorAttrib, uvAttrib;
	
	vertexAttrib.Index			= 0;
	vertexAttrib.ComponentCount = 3;
	vertexAttrib.Stride		    = 8 * sizeof(GLfloat);
	vertexAttrib.ByteOfffset    = 0;

	colorAttrib.Index		    = 1;
	colorAttrib.ComponentCount  = 3;
	colorAttrib.Stride		    = 8 * sizeof(GLfloat);
	colorAttrib.ByteOfffset     = 3 * sizeof(GLfloat);

	uvAttrib.Index              = 2;
	uvAttrib.ComponentCount	    = 2;
	uvAttrib.Stride             = 8 * sizeof(GLfloat);
	uvAttrib.ByteOfffset        = 6 * sizeof(GLfloat);

	#pragma endregion

	vao.RegisterAttribute(vbo.get(), vertexAttrib);
	vao.RegisterAttribute(vbo.get(), colorAttrib);
	vao.RegisterAttribute(vbo.get(), uvAttrib);
}

int main()
{
	using namespace Gene::Platform;
	using namespace Gene::Graphics;
	using namespace Gene::Math;
	using namespace Gene::IO;
	using namespace Gene::Input;

	WindowInfo info;
	info.Width = 800;
	info.Height = 600;
	info.Title = "Hello World!";
	info.Borderless = false;

	Window *window = Window::CreateWindow(info);
	window->Create();
	window->CreateGLContext();

	GLSLShader shader;
	shader.CompileFromFiles("Data/vertex.glsl", "Data/fragment.glsl");
	shader.Enable();

	window->SetWindowResizeCallback([](int w, int h) {
		glViewport(0, 0, w, h);
	});

	Texture2D texture("Data/brickTexture.png");
	texture.Filtering = Texture2D::FilteringOptions::Linear;
	texture.Enable();	
	
	window->SetClearColor(Color::Black);

	Buffer *ebo;
	VertexArray vao;
	CreateTriangle(vao, &ebo);

	Matrix4 matrix = Matrix4::Perpective(800 / 600, 90, 1, 0.01);
	shader.LoadUniformMatrix4f("u_Matrix", matrix);
	
	window->Show();
	
	float x = 1;
	while (window->Running())
	{
		window->PollEvents();


		KeyboardState s = Keyboard::GetState();
		if (s.IsKeyDown(Keys::W))
		{
			x += 0.04f;
		}
		else if (s.IsKeyDown(Keys::S))
		{
			x -= 0.04f;
		}
		x = Maths::Clamp(x, 0.25f, 1.75f);
		Matrix4 transform = Matrix4::Identity();
		Vector2 mPos = Mouse::GetState().Position;
		transform.Scale(x);
		shader.LoadUniformMatrix4f("u_Transform", transform);
		//transform.Translate({0.f, 0.f, 100.f});
		
		vao.DebugDrawElements(ebo);
		window->SwapBuffers();
	}

	return 0;
}