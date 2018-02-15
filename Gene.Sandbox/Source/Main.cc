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
#include <Graphics/Renderer2D.h>
#include <Debug/Logger.h>

void CreateModelMesh(
        Gene::Graphics::VertexArray &vao,
        Gene::Graphics::Buffer **ebo,
        Gene::Content::GeneModel *model
);

void gen_random(char *s, int l) {
    for (int c; c = rand() % 62, *s++ = (c + "07="[(c + 16) / 26])*(l-->0););
}

int main()
{
    using namespace Gene::Platform;
	using namespace Gene::Graphics;
	using namespace Gene::Math;
	using namespace Gene::Input;
	using namespace Gene::Content;
    using namespace Gene;
	WindowInfo info;
	info.Width = 800;
	info.Height = 600;
	info.Title = "Hello from GeneEngine.Sandbox";
	info.Borderless = false;

	Window *window = Window::CreateWindow(info);
	window->Create();
	window->CreateGLContext();
    window->SetClearColor(Color(0x1E1E1EFF));

    window->SetWindowResizeCallback([](int w, int h) {
        glViewport(0, 0, w, h);
    });

    GLSLShader *shader3d = ShaderFactory::CreateShader("Data/vertex.shader", "Data/fragment.shader", 
    {
        {0, "position"},
        {1, "normal"},
        {2, "tex_coord"}
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

    Renderer2D renderer;
    renderer.Init(Matrix4::Orthographic(info.Width, 0, 0, info.Height, 1.0f, -1.0f));
    Font font("Data/Fonts/segoeui.ttf", 7);
    
    std::string str = "The quick brown fox\njumps over the\n\nlazy dog";
    float strW = font.MeasureString(str).X;
    float xPos = info.Width / 2 - (strW / 2);

    GameTime gameTime;
	gameTime.Init();
    while (window->Running())
    {
		gameTime.StartFrame();

        // 3D rendering code
        {
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
        }
        
        // 2D rendering code
        {
            renderer.Begin();
            renderer.DrawTexture({10, 10}, font.GLTexture());

            renderer.DrawString(&font, str, { xPos, 300 }, Color(0xC8C8C8FF));

            renderer.End();
            renderer.Present();
        }

        window->SwapBuffers();
		window->PollEvents();

		gameTime.EndFrame();
		gameTime.Sleep(1000 / 60);
	}

	return 0;
}

struct Vertex 
{
    Gene::Vector3 position;
    Gene::Vector3 normal;
    Gene::Vector2 uv;
};


void CreateModelMesh(Gene::Graphics::VertexArray& vao, Gene::Graphics::Buffer** ebo, Gene::Content::GeneModel *model)
{
    using namespace Gene::Graphics;
    using namespace Gene::OpenGL;
    using namespace Gene;
    Gene::Array<Vertex> data;

    std::shared_ptr<Buffer> vbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
    
    (*ebo) = new Buffer(Buffer::Type::ElementBuffer);

    vao.Enable();

    data.reserve(model->Vertices.size() + model->Normals.size() + model->UVs.size());

    const Array<Vector3> vertices = model->Vertices;
    const Array<Vector3> normals = model->Normals;
    const Array<Vector2> uvs = model->UVs;

    for (size_t i = 0; i < model->Vertices.size(); ++i)
    {
        data.push_back({ vertices[i], normals[i],uvs[i] });
    }

    BufferDescriptor vertexBufferDesc;
    vertexBufferDesc.Data		 = &(data[0]);
    vertexBufferDesc.DataType	 = GLType::Float;
    vertexBufferDesc.Size		 = data.size() * sizeof(Vertex);
    vertexBufferDesc.DrawType	 = BufferDrawType::Static;
    vbo->SetData(vertexBufferDesc);

    BufferDescriptor indexBufferDesc;
    indexBufferDesc.Data		 = &(model->Indices[0]);
    indexBufferDesc.DataType	 = GLType::UnsignedInt;
    indexBufferDesc.Size		 = model->Indices.size() * sizeof(GLuint);
    indexBufferDesc.DrawType	 = BufferDrawType::Static;
    (*ebo)->SetData(indexBufferDesc);

    #pragma region Attributes

    int32 stride = sizeof(Vertex);

    AttributeDescriptor vertexAttrib;
    vertexAttrib.Index			  = 0;
    vertexAttrib.ComponentCount   = 3;
    vertexAttrib.Stride			  = stride;
    vertexAttrib.ByteOfffset      = offsetof(Vertex, position);
	
    AttributeDescriptor normalAttrib;
    normalAttrib.Index			  = 1;
    normalAttrib.ComponentCount   = 3;
    normalAttrib.Stride		      = stride;
    normalAttrib.ByteOfffset	  = offsetof(Vertex, normal);

    AttributeDescriptor texCoordAttrib;
    texCoordAttrib.Index          = 2;
    texCoordAttrib.ComponentCount = 2;
    texCoordAttrib.Stride         = stride;
    texCoordAttrib.ByteOfffset    = offsetof(Vertex, uv);

    #pragma endregion

    vao.RegisterAttribute(vbo.get(), vertexAttrib);
    vao.RegisterAttribute(vbo.get(), normalAttrib);
    vao.RegisterAttribute(vbo.get(), texCoordAttrib);
}

