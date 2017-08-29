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

static void CreateTriangle(Gene::Graphics::VertexArray& vao, Gene::Graphics::Buffer** ebo, Gene::Content::GeneModel *model)
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

int main()
{
	using namespace Gene::Platform;
	using namespace Gene::Graphics;
	using namespace Gene::Math;
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
    shader.BindAttributeIndex(1, "normal");
	
    window->SetWindowResizeCallback([](int w, int h) {
		glViewport(0, 0, w, h);
	});
	
	window->SetClearColor(Color::CornflowerBlue);
	OBJModelLoader loader;
	GeneModel *model = loader.Load("Data/suzanne.obj");

	Buffer *ebo;
	VertexArray vao;
	CreateTriangle(vao, &ebo, model);

	Matrix4 matrix = Matrix4::Perpective(800 / 600, 45, 100, 0.1f);
	shader.LoadUniformMatrix4f("u_Projection", matrix);
	Vector3 lightPos= Vector3(0, 10, 0);
	window->Show();
	shader.LoadUniform3f("u_LightPos", lightPos);

    glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	
	float theta = 180.f;
	
	Vector3 pos(0, 0, -5.f);

    while (window->Running())
	{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		std::cout << lightPos.X << ", " << lightPos.Y << std::endl;
  	    Matrix4 transform = Matrix4::Identity();
		transform.Translate(pos);
		transform.RotateY(theta);
	    shader.LoadUniformMatrix4f("u_Transform", transform);
		//theta += 1.f;
    	vao.DebugDrawElements(ebo);

        KeyboardState state = Keyboard::GetState();
//		state.KeyMap[(int)Keys::D] = true;
        if (state.IsKeyDown(Keys::D)) {
			lightPos.X += 1.f;
			shader.LoadUniform3f("u_LightPos", lightPos);
		}
		else if(state.IsKeyDown(Keys::A)) {
			lightPos.X -= 1.f;
			shader.LoadUniform3f("u_LightPos", lightPos);
		}

		if (state.IsKeyDown(Keys::W)) {
			lightPos.Y += 1.f;
			shader.LoadUniform3f("u_LightPos", lightPos);
		}
		else if (state.IsKeyDown(Keys::S)) {
			lightPos.Y -= 1.f;
			shader.LoadUniform3f("u_LightPos", lightPos);
		}

        window->SwapBuffers();
		window->PollEvents();
	}

	return 0;
}
