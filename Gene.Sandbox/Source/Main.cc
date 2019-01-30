#include <Content/OBJModelLoader.h>
#include <Runtime/Application.h>
#include <experimental/filesystem>
#include <Graphics/VertexArray.h>
#include <Graphics/GLSLShader.h>
#include <Graphics/Factorys/ShaderFactory.h>
#include <Graphics/Texture2D.h>
#include <Math/Matrix4.h>
#include <Math/Vector3.h>

void CopyAssetsDirectory(const gene::String& subdir = "")
{
	namespace fs = std::experimental::filesystem;
	fs::copy(ASSETS_DIRECTORY + subdir, ASSETS_OUT_DIRECTORY + subdir, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}

void CreateModelMesh(gene::graphics::VertexArray& vao, gene::graphics::Buffer** ebo, gene::runtime::GeneModel *model)
{
	using namespace gene::graphics;
	using namespace gene::opengl;

	std::shared_ptr<Buffer> vbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
	std::shared_ptr<Buffer> tbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);
	std::shared_ptr<Buffer> nbo = std::make_shared<Buffer>(Buffer::Type::ArrayBuffer);

	(*ebo) = new Buffer(Buffer::Type::ElementBuffer);

	vao.Enable();

	BufferDescriptor vertexBufferDesc;
	vertexBufferDesc.Data = &(model->Vertices[0]);
	vertexBufferDesc.DataType = GLType::Float;
	vertexBufferDesc.Size = model->Vertices.size() * 3 * sizeof(GLfloat);
	vertexBufferDesc.DrawType = BufferDrawType::Static;
	vbo->SetData(vertexBufferDesc);

	BufferDescriptor normalBufferDesc;
	normalBufferDesc.Data = &(model->Normals[0]);
	normalBufferDesc.DataType = GLType::Float;
	normalBufferDesc.Size = model->Normals.size() * 3 * sizeof(GLfloat);
	normalBufferDesc.DrawType = BufferDrawType::Static;
	nbo->SetData(normalBufferDesc);

	BufferDescriptor texCoordBufferDesc;
	texCoordBufferDesc.Data = &(model->UVs[0]);
	texCoordBufferDesc.DataType = GLType::Float;
	texCoordBufferDesc.Size = model->UVs.size() * 2 * sizeof(GLfloat);
	texCoordBufferDesc.DrawType = BufferDrawType::Static;
	tbo->SetData(texCoordBufferDesc);

	BufferDescriptor indexBufferDesc;
	indexBufferDesc.Data = &(model->Indices[0]);
	indexBufferDesc.DataType = GLType::UnsignedInt;
	indexBufferDesc.Size = model->Indices.size() * sizeof(GLuint);
	indexBufferDesc.DrawType = BufferDrawType::Static;
	(*ebo)->SetData(indexBufferDesc);

	AttributeDescriptor vertexAttrib;
	vertexAttrib.Index = 0;
	vertexAttrib.ComponentCount = 3;
	vertexAttrib.Stride = 0;
	vertexAttrib.ByteOfffset = 0;

	AttributeDescriptor texCoordAttrib;
	texCoordAttrib.Index = 1;
	texCoordAttrib.ComponentCount = 2;
	texCoordAttrib.Stride = 0;
	texCoordAttrib.ByteOfffset = 0;

	AttributeDescriptor normalAttrib;
	normalAttrib.Index = 2;
	normalAttrib.ComponentCount = 3;
	normalAttrib.Stride = 0;
	normalAttrib.ByteOfffset = 0;

	vao.RegisterAttribute(vbo.get(), vertexAttrib);
	vao.RegisterAttribute(tbo.get(), texCoordAttrib);
	vao.RegisterAttribute(nbo.get(), normalAttrib);
}

class OBJModelDemo : public gene::App {
public:
	gene::graphics::GLSLShader *shader3d;

	float suzanneTheta = 180.f;
	gene::Vector3 suzannePosition;
	gene::graphics::VertexArray *vao;
	gene::graphics::Buffer *ebo;
	gene::graphics::Texture2D* texture;
	bool rotate = true;
	
    virtual void Init() override { 
        using namespace gene;
		using namespace gene::graphics;

		CopyAssetsDirectory();
		suzannePosition = { 0.f, 0.f, -5.f };

		platform::Window *window = GetWindow();
        window->SetClearColor(gene::graphics::Color(79, 87, 99, 255));

		shader3d = graphics::ShaderFactory::CreateShader("Data/Shaders/Renderer3DVertex.shader", "Data/Shaders/Renderer3DFragment.shader",
			{
				{0, "position"},
				{1, "tex_coord"},
				{2, "normal"}
			});
		shader3d->Enable();

		runtime::IModelLoader *objModelLoader = new runtime::OBJModelLoader();
		runtime::GeneModel* model = objModelLoader->Load("Data/Models/doughnut.obj");
	
		vao = new VertexArray;
		CreateModelMesh(*vao, &ebo, model);

		Matrix4 perspectiveMatrix = Matrix4::Perpective(static_cast<float>(window->Width() / window->Height()), 45, 1000, 0.001f);
		shader3d->LoadUniformMatrix4f("u_Projection", perspectiveMatrix);
		shader3d->LoadUniform3f("light_pos", { 100000.0f,0,0 });
		texture = new Texture2D("Data/Models/doughnut_texture.png");

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
	}  
	 
	bool spaceWasDown = false;
    virtual void Tick(const gene::platform::GameTime& time) override {
		if (rotate) {
			suzanneTheta += 1.f;
		}
		
		bool spaceDown = GetWindow()->GetInputController()->GetKeyDevice()->IsKeyPressed(gene::input::Keys::Space);
		if (spaceDown && !spaceWasDown) {
			rotate = !rotate;
		}

		if (GetWindow()->GetInputController()->GetKeyDevice()->IsKeyPressed(gene::input::Keys::UpArrow)) {
			suzannePosition.Z += 1.f;
		}

		if (GetWindow()->GetInputController()->GetKeyDevice()->IsKeyPressed(gene::input::Keys::DownArrow)) {
			suzannePosition.Z -= 1.f;
		}

		spaceWasDown = spaceDown;
	}
	 
    virtual void Draw() override {
		shader3d->Enable();

		gene::Matrix4 rx = gene::Matrix4::RotateX(suzanneTheta);
		gene::Matrix4 ry = gene::Matrix4::RotateY(suzanneTheta);
		
		gene::Matrix4 transform = gene::Matrix4::Translate(suzannePosition) * rx * ry;

		shader3d->LoadUniformMatrix4f("u_Transform", transform);

		glEnable(GL_DEPTH_TEST);
		texture->Enable(0);
		vao->Enable();
		ebo->Enable();
		glDrawElements(GL_TRIANGLES, ebo->Size()/sizeof(GLuint), GL_UNSIGNED_INT, NULL);
		ebo->Disable();
		vao->Disable();
		texture->Disable(0);

		shader3d->Disable();
		glDisable(GL_DEPTH_TEST);
    }
    
    virtual void GuiDraw() override {
	}
};

int GeneMain(int argc, char **argv)
{ 
    gene::App* mapDemo = new OBJModelDemo();
    mapDemo->Run(1280, 720, "App Demo!");

    return 0;
}
