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
#include <Graphics/PreBuiltVertices.h>

static void CreateTriangle(Gene::Graphics::VertexArray& vao, Gene::Graphics::Buffer** ebo)
{
	using namespace Gene::Graphics;
	
	std::shared_ptr<Buffer> vbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
	
	vao.Enable();
	
	BufferDescriptor vertexBufferDesc;
	vertexBufferDesc.Data     = PreBuiltVertices::RectangleVertices;
	vertexBufferDesc.DataType = Gene::OpenGL::GLType::Float;
	vertexBufferDesc.Size     = sizeof(PreBuiltVertices::RectangleVertices);
	vertexBufferDesc.DrawType = BufferDrawType::Static;
	vbo->SetData(vertexBufferDesc);

	(*ebo) = new Buffer(Buffer::Type::ElementBuffer);
	BufferDescriptor indexBufferDesc;
	indexBufferDesc.Data = PreBuiltVertices::RectangleIndices;
	indexBufferDesc.DataType  = Gene::OpenGL::GLType::UnsignedInt;
	indexBufferDesc.Size      = sizeof(PreBuiltVertices::RectangleIndices);
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
	info.Width = 600;
	info.Height = 400;
	info.Title = "Hello World!";
	info.Borderless = false;

	Window *window = Window::CreateWindow(info);
	window->Create();
	window->CreateGLContext();

	GLSLShader shader;
	shader.CompileFromFiles("Data/vertex.glsl", "Data/fragment.glsl");
    shader.Enable();
    shader.BindAttributeIndex(0, "position");
    shader.BindAttributeIndex(1, "color");
    shader.BindAttributeIndex(2, "uv");
	
    window->SetWindowResizeCallback([](int w, int h) {
		glViewport(0, 0, w, h);
	});

	Texture2D texture("Data/brickTexture.png");
	texture.Filtering = Texture2D::FilteringOptions::Linear;
	texture.Enable();	
	
	window->SetClearColor(Color::CornflowerBlue);

	Buffer *ebo;
	VertexArray vao;
	CreateTriangle(vao, &ebo);

	Matrix4 matrix = Matrix4::Perpective(800 / 600, 90, 100, 0.1f);
	shader.LoadUniformMatrix4f("u_Matrix", matrix);
	
	window->Show();
	
    glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

    while (window->Running())
	{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
  	    Matrix4 transform = Matrix4::Identity();
	    shader.LoadUniformMatrix4f("u_Transform", transform);
        MouseState state = Mouse::GetState();
        
    	vao.DebugDrawElements(ebo);
		
        window->SwapBuffers();
		window->PollEvents();
	}

	return 0;
}
