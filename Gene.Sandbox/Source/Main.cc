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
#include <Input/Mouse.h>
#include <sstream>
#include <iomanip>
#include <Graphics/Factorys/ShaderFactory.h>

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
        {1, "normal"}
    });
    shader3d->Enable();

	OBJModelLoader objLoader;
	GeneModel *suzanneModel = objLoader.Load("Data/suzanne.obj");

	Buffer *modelEbo;
	VertexArray modelVao;
    CreateModelMesh(modelVao, &modelEbo, suzanneModel);

    Font wendyOneFont("Data/impact.ttf", 48);

	Matrix4 perspectiveMatrix = Matrix4::Perpective(static_cast<float>(info.Width / info.Height), 45, 1000, 0.001f);
	shader3d->LoadUniformMatrix4f("u_Projection", perspectiveMatrix);

	Renderer2D renderer2d;
	renderer2d.Init(
        Matrix4::Orthographic(static_cast<float>(info.Width), 0.f, 0.f, static_cast<float>(info.Height), 1.f, -1.f)
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

    while (window->Running())
    {
		KeyboardState state = Keyboard::GetState();
		gameTime.StartFrame();
        shader3d->Enable();

        suzanneTheta += 1.f;
  	    Matrix4 transform = Matrix4::Identity();
		transform.Translate(suzannePosition);
		transform.RotateY(suzanneTheta);
	    shader3d->LoadUniformMatrix4f("u_Transform", transform);

        window->Clear();

		glEnable(GL_DEPTH_TEST);
        modelVao.Enable();
        modelEbo->Enable();
    	modelVao.DebugDrawElements(modelEbo);
        modelEbo->Disable();
        modelVao.Disable();
        shader3d->Disable();
        glDisable(GL_DEPTH_TEST);

        renderer2d.Begin();

        renderer2d.DrawTexture(pos, &texture1);
        renderer2d.DrawTexture(pos + Vector2(0, 100), &texture2);

        renderer2d.FillRectangle({425, 50}, 100, 100, Color::Blue);

        MouseState mState = Mouse::GetState();
        std::string s = std::to_string((int)mState.Position.X) + ", " + std::to_string((int)mState.Position.Y);
        renderer2d.DrawString(&wendyOneFont, s, {0, 375}, Color::Red);
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

