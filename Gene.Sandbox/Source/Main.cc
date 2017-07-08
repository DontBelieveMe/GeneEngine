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
#include <Content/OBJModelLoader.h>
#include <GeneCommon.h>

std::vector<Gene::Math::Vector3> g_ModelData;

static void CreateTriangle(Gene::Graphics::VertexArray& vao, Gene::Graphics::Buffer** ebo, Gene::Content::GeneModel *model)
{
	using namespace Gene::Graphics;
	
	std::shared_ptr<Buffer> vbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
	
	vao.Enable();
 
    g_ModelData = Gene::MixVectors(model->Vertices, model->Normals, 3, 3);
     
	BufferDescriptor vertexBufferDesc;
    vertexBufferDesc.Data = &(g_ModelData[0]); //&(model->Vertices[0]);//PreBuiltVertices::RectangleVertices;
	vertexBufferDesc.DataType = Gene::OpenGL::GLType::Float;
    vertexBufferDesc.Size = g_ModelData.size() * sizeof(GLfloat); //sizeof(PreBuiltVertices::RectangleVertices);
	vertexBufferDesc.DrawType = BufferDrawType::Static;
	vbo->SetData(vertexBufferDesc);

	(*ebo) = new Buffer(Buffer::Type::ElementBuffer);
	BufferDescriptor indexBufferDesc;
    indexBufferDesc.Data = &(model->Indices[0]);//PreBuiltVertices::RectangleIndices;
	indexBufferDesc.DataType  = Gene::OpenGL::GLType::UnsignedInt;
    indexBufferDesc.Size = model->Indices.size() * sizeof(GLuint); //sizeof(PreBuiltVertices::RectangleIndices);
	indexBufferDesc.DrawType  = BufferDrawType::Static;
	(*ebo)->SetData(indexBufferDesc);

	#pragma region Attributes

	AttributeDescriptor vertexAttrib;
	
	vertexAttrib.Index			= 0;
	vertexAttrib.ComponentCount = 3;
	vertexAttrib.Stride		    = 6 * sizeof(GLfloat);
	vertexAttrib.ByteOfffset    = 0;

	AttributeDescriptor normalAttrib;
	normalAttrib.Index = 1;
	normalAttrib.ComponentCount = 3;
	normalAttrib.Stride = 6 * sizeof(GLfloat);
	normalAttrib.Stride = 3 * sizeof(GLfloat);

	#pragma endregion

	vao.RegisterAttribute(vbo.get(), vertexAttrib);
    vao.RegisterAttribute(vbo.get(), normalAttrib);
}

int main()
{
	using namespace Gene::Platform;
	using namespace Gene::Graphics;
	using namespace Gene::Math;
	using namespace Gene::IO;
	using namespace Gene::Input;
	using namespace Gene::Content;
    using namespace Gene;

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
	OBJModelLoader loader;
	GeneModel *model = loader.Load("Data/suzanne.obj");

	Buffer *ebo;
	VertexArray vao;
	CreateTriangle(vao, &ebo, model);

	Matrix4 matrix = Matrix4::Perpective(800 / 600, 90, 100, 0.1f);
	shader.LoadUniformMatrix4f("u_Matrix", matrix);
	 
	//GeneModel *model = new OBJModelLoader()->Load("Data/suzanne.obj");

	window->Show();
	
    std::vector<int> a = { 1,1,1,1,1,1,1,1,1 };
    std::vector<int> b = { 0,0,0,0,0,0,0,0,0 };
    std::vector<int> c = MixVectors(a, b, 3, 3);
    for(int i : c) {
        printf("%i ", i);
    }

    glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	float x = 0.f;
    while (window->Running())
	{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
  	    Matrix4 transform = Matrix4::Identity();
		transform.RotateY(x);
	    shader.LoadUniformMatrix4f("u_Transform", transform);
        //MouseState state = Mouse::GetState();
        
    	vao.DebugDrawElements(ebo);
		
		KeyboardState state = Keyboard::GetState();
		if (state.IsKeyDown(Keys::W))
		{
			x += 1.f;
		}

        window->SwapBuffers();
		window->PollEvents();
	}

	return 0;
}
