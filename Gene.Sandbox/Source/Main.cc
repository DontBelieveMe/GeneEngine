#include <Platform/Window.h>
#include <Graphics/Color.h>
#include <Graphics/Buffer.h>
#include <Graphics/VertexArray.h>
#include <Math/Math.h>
#include <memory>
#include <Content/OBJModelLoader.h>
#include <Platform/Time.h>
#include <Graphics/Factorys/ShaderFactory.h>
#include <GeneCommon.h>
#include <Graphics/Texture2D.h>

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

    WindowInfo info = { 600, 600, "Hello from GeneEngine.Sandbox", false };

	Window *window = Window::CreateWindow(info);
	window->Create();
	window->CreateGLContext();
    window->SetClearColor(Color::CornflowerBlue);

    window->SetWindowResizeCallback([](int w, int h) {
        glViewport(0, 0, w, h);
    });

    GLSLShader *shader3d = ShaderFactory::CreateShader("Data/vertex.shader", "Data/fragment.shader", 
    {
        {0, "position"},
        {1, "tex_coord"},
        {2, "normal"}
    });
    shader3d->Enable();

	OBJModelLoader objLoader;
	GeneModel *suzanneModel = objLoader.Load("Data/doughnut.obj");

	Buffer *modelEbo;
	VertexArray modelVao;
    CreateModelMesh(modelVao, &modelEbo, suzanneModel);

	Matrix4 perspectiveMatrix = Matrix4::Perpective(static_cast<float>(info.Width / info.Height), 45, 1000, 0.001f);
	shader3d->LoadUniformMatrix4f("u_Projection", perspectiveMatrix);
    shader3d->LoadUniform3f("light_pos", { 100000.0f,0,0 });
    Texture2D doughnut("Data/doughnut_texture.png");

	window->Show();
	
    float suzanneTheta = 180.f;
    Vector3 suzannePosition(0, 0, -5.f);
    
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    GameTime gameTime;
	gameTime.Init();
    while (window->Running())
    {
		gameTime.StartFrame();
        shader3d->Enable();

        suzanneTheta += 1.f;
  	    Matrix4 transform = Matrix4::Identity();
		transform.Translate(suzannePosition);
		
        Matrix4 rx, ry;
        rx.RotateX(suzanneTheta);
        ry.RotateY(suzanneTheta);

        transform = transform.Multiply(rx).Multiply(ry);

        shader3d->LoadUniformMatrix4f("u_Transform", transform);

        window->Clear();

		glEnable(GL_DEPTH_TEST);
        doughnut.Enable(0);
        modelVao.Enable();
        modelEbo->Enable();
    	modelVao.DebugDrawElements(modelEbo);
        modelEbo->Disable();
        modelVao.Disable();
        doughnut.Disable(0);

        shader3d->Disable();
        glDisable(GL_DEPTH_TEST);
       
        window->SwapBuffers();
		window->PollEvents();

		gameTime.EndFrame();
		gameTime.Sleep(1000 / 60);
	}

	return 0;
}

void CreateModelMesh(Gene::Graphics::VertexArray& vao, Gene::Graphics::Buffer** ebo, Gene::Content::GeneModel *model)
{
    using namespace Gene::Graphics;
    using namespace Gene::OpenGL;

    std::shared_ptr<Buffer> vbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
    std::shared_ptr<Buffer> tbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
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
    normalBufferDesc.Data = &(model->Normals[0]);
    normalBufferDesc.DataType = GLType::Float;
    normalBufferDesc.Size = model->Normals.size() * 3 * sizeof(GLfloat);
    normalBufferDesc.DrawType = BufferDrawType::Static;
    nbo->SetData(normalBufferDesc);

    BufferDescriptor texCoordBufferDesc;
    texCoordBufferDesc.Data		 = &(model->UVs[0]);
    texCoordBufferDesc.DataType	 = GLType::Float;
    texCoordBufferDesc.Size		 = model->UVs.size() * 2 * sizeof(GLfloat);
    texCoordBufferDesc.DrawType	 = BufferDrawType::Static;
    tbo->SetData(texCoordBufferDesc);

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
	
    AttributeDescriptor texCoordAttrib;
    texCoordAttrib.Index			 = 1;
    texCoordAttrib.ComponentCount    = 2;
    texCoordAttrib.Stride		     = 0;
    texCoordAttrib.ByteOfffset	     = 0;

    AttributeDescriptor normalAttrib;
    normalAttrib.Index = 2;
    normalAttrib.ComponentCount = 3;
    normalAttrib.Stride = 0;
    normalAttrib.ByteOfffset = 0;


    #pragma endregion

    vao.RegisterAttribute(vbo.get(), vertexAttrib);
    vao.RegisterAttribute(tbo.get(), texCoordAttrib);
    vao.RegisterAttribute(nbo.get(), normalAttrib);
}

