#include <Platform/Window.h>
#include <Graphics/Color.h>
#include <Graphics/Renderer2D.h>
#include <Platform/Time.h>
#include <Math/Math.h>
#include <Graphics/Buffer.h>
#include <Content/OBJModelLoader.h>
#include <Runtime/Application.h>
#include <Input/InputController.h>
#include <Graphics/ImGui.h>
#include <Scripting/LuaJIT.h>
#include <Runtime/Reflection.h>
#include <Runtime/ECS.h>
#include <filesystem>

void CopyAssetsDirectory(const gene::String& subdir = "")
{
	namespace fs = std::experimental::filesystem;
	fs::copy(ASSETS_DIRECTORY + subdir, ASSETS_OUT_DIRECTORY + subdir, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}

class ClearColorDemo : public gene::App {
	gene::graphics::Renderer2D m_2drenderer;
	gene::graphics::Texture2D m_StoneTexture, m_CrateTexture;

	gene::graphics::Light *m_light, *m_light2;
	gene::graphics::Font m_font;
public:
    
    virtual void Init() override { 
        using namespace gene;
		CopyAssetsDirectory();
			
        platform::Window *window = GetWindow();
        window->SetClearColor(gene::graphics::Color::Black/*gene::graphics::Color(79, 87, 99, 255)*/);
		   
		m_2drenderer.Init(Matrix4::Orthographic(window->Width(), 0.f, 0.f, window->Height(), 100.f, -1.0f));
		
		gene::graphics::TextureParameters p;  
		
		p.Filtering = gene::graphics::FilteringOptions::Nearest;
		m_font.Load("Data/Fonts/Gidole-Regular.ttf");
		m_StoneTexture.Load("Data/stone.png", p);
		m_CrateTexture.Load("Data/crate.png", p);

		m_light = new graphics::Light {
			Vector3(32,32,0.f),
			300.f,
			1.5f,
			1.0f,
			graphics::Color::Red
		};

		m_light2 = new graphics::Light {
			Vector3(200,200,0.f),
			300.f,
			1.5f,
			1.0f,
			graphics::Color::Green
		};
		
		Array<graphics::Light*> lights;
		lights.push_back(m_light);
		lights.push_back(m_light2);

		m_2drenderer.LoadLights(lights);
	}  
	 
    virtual void Tick(const gene::platform::GameTime& time) override {
		using namespace gene;

		platform::Window* window = GetWindow();
		input::MouseDevice* mouse = window->GetInputController()->GetMouseDevice();
		Vector2i mousePos = mouse->GetCursorPosition();
		Vector3 pos = {
			(float)mousePos.X,
			(float)mousePos.Y,
			0.f
		};
		m_light->Position = pos;
		pos.X -= 100;
		m_light2->Position = pos;

		graphics::GLSLShader *shader = m_2drenderer.GetShader();
		shader->Enable();
		m_2drenderer.LoadLight(m_light, 0);
		m_2drenderer.LoadLight(m_light2, 1);
		shader->Disable();
	}
	 
    virtual void Draw() override {       
		m_2drenderer.Begin();

		m_2drenderer.PushTransform(gene::Matrix4::Scale((4.f)));  
		 
		for (float y = 3; y < 10; y++) {
			for (float x = 3; x < 10; x++) {
				m_2drenderer.DrawTexture({ x*16.f, y*16.f, 0.f }, &m_StoneTexture);
			}
		}
		m_2drenderer.DrawTexture({ 4*16.f,4*16.f, 0.f}, &m_CrateTexture);
		
		m_2drenderer.PopTransform(); 
		m_2drenderer.DrawString(&m_font, "Hello World!", { 100.f, 100.f }, gene::graphics::Color(1.0f,1.0f,0.0f,1.0f));
		m_2drenderer.End();
		m_2drenderer.Present();
    }
     
	float m_ambient = 0.1f;

    virtual void GuiDraw() override {
		ImGui::Begin("Assets");
		if (ImGui::Button("Refresh Assets Directory")) {
			CopyAssetsDirectory();
		}
		ImGui::Separator();
		ImGui::Text("Shaders");
		if (ImGui::Button("Reload Shaders")) {
			CopyAssetsDirectory("Shaders/");
			m_2drenderer.LoadShaders();
		}

		if (ImGui::DragFloat("Ambient Lighting", &m_ambient, 0.01f, 0.0f, 1.0f)) {
			m_2drenderer.GetShader()->Enable();
			m_2drenderer.GetShader()->LoadUniform1f("u_Ambient", m_ambient);
			m_2drenderer.GetShader()->Disable();
		}
		
		ImGui::End();
	}
};

int GeneMain(int argc, char **argv)
{ 
    gene::App* mapDemo = new ClearColorDemo();
    mapDemo->Run(1280, 720, "App Demo!");

    return 0;
}
