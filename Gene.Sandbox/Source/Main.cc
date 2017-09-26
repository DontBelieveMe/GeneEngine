#include <Platform/Window.h>
#include <Graphics/GLSLShader.h>
#include <Math/Vector3.h>
#include <Graphics/Color.h>
#include <Graphics/Buffer.h>
#include <Platform/OpenGL.h>
#include <Graphics/VertexArray.h>
#include <Math/Math.h>
#include <memory>
#include <Content/OBJModelLoader.h>
#include <GeneCommon.h>
#include <Graphics/Light.h>
#include <Input/Keyboard.h>
#include <Graphics/Font.h>
#include <Graphics/Renderer2D.h>

void CreateTriangle(
        Gene::Graphics::VertexArray &vao,
        Gene::Graphics::Buffer **ebo,
        Gene::Content::GeneModel *model
);

int main()
{
	using namespace Gene::Platform;
	using namespace Gene::Graphics;
	using namespace Gene::Math;
	using namespace Gene::Input;
	using namespace Gene::Content;
    using namespace Gene;

    WindowInfo info = { 600, 400, "Hello from GeneEngine.Sandbox", false };

	Window *window = Window::CreateWindow(info);
	window->Create();
	window->CreateGLContext();
    window->SetClearColor(Color::CornflowerBlue);

    window->SetWindowResizeCallback([](int w, int h) {
        glViewport(0, 0, w, h);
    });

	GLSLShader shader;
	shader.CompileFromFiles("Data/vertex.glsl", "Data/fragment.glsl");
    shader.Enable();
    shader.BindAttributeIndex(0, "position");
    shader.BindAttributeIndex(1, "normal");
	
	OBJModelLoader loader;
	GeneModel *model = loader.Load("Data/suzanne.obj");

	Buffer *ebo;
	VertexArray vao;
	CreateTriangle(vao, &ebo, model);

    Font wendyOneFont("Data/WendyOne-Regular.ttf");

	Matrix4 matrix = Matrix4::Perpective(800 / 600, 45, 100, 0.1f);
	shader.LoadUniformMatrix4f("u_Projection", matrix);

    glEnable(GL_DEPTH_TEST);
    float theta = 180.f;
    Vector3 pos(0, 0, -5.f);

	Renderer2D renderer;
	renderer.Init();
	
	window->Show();
	
    while (window->Running())
	{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	    Matrix4 transform = Matrix4::Identity();
		transform.Translate(pos);
		transform.RotateY(theta);
	    shader.LoadUniformMatrix4f("u_Transform", transform);
		theta += 1.f;
    	vao.DebugDrawElements(ebo);

        const KeyboardState& keys = Keyboard::GetState();
        if(keys.IsKeyDown(Keys::W))
            pos.Z += 0.3f;
        else if(keys.IsKeyDown(Keys::S))
            pos.Z -= 0.3f;

        window->SwapBuffers();
		window->PollEvents();
	}

	return 0;
}

void CreateTriangle(Gene::Graphics::VertexArray& vao, Gene::Graphics::Buffer** ebo, Gene::Content::GeneModel *model)
{
    using namespace Gene::Graphics;
    using namespace Gene::OpenGL;

    std::shared_ptr<Buffer> vbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
    std::shared_ptr<Buffer> nbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);

    (*ebo) = new Buffer(Buffer::Type::ElementBuffer);

    vao.Enable();

    BufferDescriptor vertexBufferDesc;
    vertexBufferDesc.Data		 = &(model->Vertices[0]);
    vertexBufferDesc.DataType	 = GLType::Float;
    vertexBufferDesc.Size		 = model->Vertices.size() * 3 * sizeof(GLfloat);
    vertexBufferDesc.DrawType	 = BufferDrawType::Static;
    vbo->SetData(vertexBufferDesc);

    BufferDescriptor normalBufferDesc;
    normalBufferDesc.Data		 = &(model->Normals[0]);
    normalBufferDesc.DataType	 = GLType::Float;
    normalBufferDesc.Size		 = model->Normals.size() * 3 * sizeof(GLfloat);
    normalBufferDesc.DrawType	 = BufferDrawType::Static;
    nbo->SetData(normalBufferDesc);

    BufferDescriptor indexBufferDesc;
    indexBufferDesc.Data		 = &(model->Indices[0]);
    indexBufferDesc.DataType	 = GLType::UnsignedInt;
    indexBufferDesc.Size		 = model->Indices.size() * sizeof(GLuint);
    indexBufferDesc.DrawType	 = BufferDrawType::Static;
    (*ebo)->SetData(indexBufferDesc);

    #pragma region Attributes

    AttributeDescriptor vertexAttrib;
    vertexAttrib.Index			 = 0;
    vertexAttrib.ComponentCount  = 3;
    vertexAttrib.Stride			 = 0;
    vertexAttrib.ByteOfffset     = 0;

    AttributeDescriptor normalAttrib;
    normalAttrib.Index			 = 1;
    normalAttrib.ComponentCount  = 3;
    normalAttrib.Stride		     = 0;
    normalAttrib.ByteOfffset	 = 0;

    #pragma endregion

    vao.RegisterAttribute(vbo.get(), vertexAttrib);
    vao.RegisterAttribute(nbo.get(), normalAttrib);
}

