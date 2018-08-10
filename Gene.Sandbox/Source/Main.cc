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
	gene::graphics::Texture2D m_texture;
public:
    
    virtual void Init() override { 
        using namespace gene;
		CopyAssetsDirectory();
			
        platform::Window *window = GetWindow();
        window->SetClearColor(gene::graphics::Color::Black/*gene::graphics::Color(79, 87, 99, 255)*/);
		   
		m_2drenderer.Init(Matrix4::Orthographic(window->Width(), 0.f, 0.f, window->Height(), 100.f, -1.0f));
		
		gene::graphics::TextureParameters p;  
		p.Filtering = gene::graphics::FilteringOptions::Nearest;
		m_texture.Load("Data/grass.png", p);  
	}  
	 
    virtual void Tick(const gene::platform::GameTime& time) override {
		auto mouse = GetWindow()->GetInputController()->GetMouseDevice();
		m_2drenderer.GetShader()->Enable();
		m_2drenderer.GetShader()->LoadUniform4f("u_LightPos", { (float)mouse->GetCursorPosition().X, GetWindow()->Height() - (float)mouse->GetCursorPosition().Y, 0.0f, 1.0f });

		m_2drenderer.GetShader()->Disable();

    }
	 
    virtual void Draw() override {       
		m_2drenderer.Begin();

		m_2drenderer.PushTransform(gene::Matrix4::Scale((4.f)));  
		 
		for (float y = 3; y < 10; y++) {
			for (float x = 3; x < 10; x++) {
				m_2drenderer.DrawTexture({x * 16.f,y * 16.f, 0.f}, &m_texture);
			}
		}
		
		m_2drenderer.PopTransform(); 
		m_2drenderer.End();
		m_2drenderer.Present();
    }
      
    virtual void GuiDraw() override {
		ImGui::Begin("Assets");
		if (ImGui::Button("Refresh Assets Directory")) {
			CopyAssetsDirectory();
		}

		if (ImGui::Button("Reload Shaders")) {
			CopyAssetsDirectory("Shaders/");
			m_2drenderer.LoadShaders();
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
