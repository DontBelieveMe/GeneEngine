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
#include <Platform/Time.h>
#include <Graphics/Light.h>
#include <Input/Keyboard.h>
#include <Graphics/Font.h>
#include <Graphics/Renderer2D.h>

void CreateModelMesh(
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
    window->SetClearColor(Color::Green);

    window->SetWindowResizeCallback([](int w, int h) {
        glViewport(0, 0, w, h);
    });

	GLSLShader shader3d;
	shader3d.CompileFromFiles("Data/vertex.glsl", "Data/fragment.glsl");
    shader3d.Enable();
    shader3d.BindAttributeIndex(0, "position");
    shader3d.BindAttributeIndex(1, "normal");
	
	OBJModelLoader objLoader;
	GeneModel *suzanneModel = objLoader.Load("Data/suzanne.obj");

	Buffer *modelEbo;
	VertexArray modelVao;
    CreateModelMesh(modelVao, &modelEbo, suzanneModel);

    Font wendyOneFont("Data/WendyOne-Regular.ttf", 80);

	Matrix4 perspectiveMatrix = Matrix4::Perpective(info.Width / info.Height, 45, 100, 0.1f);
	shader3d.LoadUniformMatrix4f("u_Projection", perspectiveMatrix);

	GLSLShader shader2d;
	shader2d.CompileFromFiles("Data/vertex2d.glsl", "Data/fragment2d.glsl");
	shader2d.Enable();
	shader2d.BindAttributeIndex(0, "position");
	shader2d.BindAttributeIndex(1, "color");
	shader2d.BindAttributeIndex(2, "uv");
	shader2d.BindAttributeIndex(3, "texId");

	Renderer2D renderer2d;
	renderer2d.Init(
        Matrix4::Orthographic(info.Width, 0, 0, info.Height, 1.f, -1.f),
		&shader2d
	);

    Texture2D texture1;
    texture1.Filtering = Texture2D::FilteringOptions::Linear;
    texture1.Load("Data/face.png");

    Texture2D texture2;
    texture2.Filtering = Texture2D::FilteringOptions::Linear;
    texture2.Load("Data/twitter.png");

    
	window->Show();
	
    float suzanneTheta = 180.f;
    Vector3 suzannePosition(0, 0, -5.f);
	Vector2 pos(10, 10);
	GameTime gameTime;
	gameTime.Init();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (window->Running())
    {
		KeyboardState state = Keyboard::GetState();
		gameTime.StartFrame();
        std::cout << gameTime.DeltaInMilliSeconds() << std::endl;
        shader3d.Enable();
		
        suzanneTheta += 1.f;
  	    Matrix4 transform = Matrix4::Identity();
		transform.Translate(suzannePosition);
		transform.RotateY(suzanneTheta);
	    shader3d.LoadUniformMatrix4f("u_Transform", transform);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
        modelVao.Enable();
        modelEbo->Enable();
    	modelVao.DebugDrawElements(modelEbo);
        modelEbo->Disable();
        modelVao.Disable();
        shader3d.Disable();
        glDisable(GL_DEPTH_TEST);


        renderer2d.Begin();
        renderer2d.DrawTexture(pos, &texture1);
        
        //renderer2d.DrawTexture(pos + Vector2(0, 100), &texture2);
        renderer2d.FillRectangle({425, 50}, 100, 100, Color::Blue);

        renderer2d.DrawString(&wendyOneFont, "Hello World!", {50, 50}, Color::CornflowerBlue);
		renderer2d.End();
        renderer2d.Present();

        window->SwapBuffers();
		window->PollEvents();
		gameTime.EndFrame();
		gameTime.Sleep(1000 / 60);
	}
	
	renderer2d.Destroy();

	return 0;
}

void CreateModelMesh(Gene::Graphics::VertexArray& vao, Gene::Graphics::Buffer** ebo, Gene::Content::GeneModel *model)
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

