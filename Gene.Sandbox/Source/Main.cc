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

META_CLASS_REFLECT_IMPL(gene::MemberObjectNested)
	META_CLASS_DECLARE_MEMBER(gene::Vector3, RandomVector3)
	META_CLASS_DECLARE_MEMBER(int, RandomInteger)
META_CLASS_END_REFLECT_IMPL()

META_CLASS_REFLECT_IMPL(gene::GameObject)
	META_CLASS_DECLARE_MEMBER(gene::Vector3, Position)
	META_CLASS_DECLARE_MEMBER(gene::graphics::Color, Colour)
	META_CLASS_DECLARE_MEMBER(int, Test)
	META_CLASS_DECLARE_MEMBER(gene::MemberObjectNested, ArbitraryObject)
META_CLASS_END_REFLECT_IMPL()

class ClearColorDemo : public gene::App {
	gene::GameObject m_object;
	gene::graphics::Renderer2D m_2drenderer;
	gene::graphics::Texture2D m_texture;
public:
    
    virtual void Init() override { 
        using namespace gene;
	
        platform::Window *window = GetWindow();
        window->SetClearColor(gene::graphics::Color::Black/*gene::graphics::Color(79, 87, 99, 255)*/);

		m_2drenderer.Init(Matrix4::Orthographic(window->Width(), 0.f, 0.f, window->Height(), 100.f, -1.0f));
		
		gene::graphics::TextureParameters p;
		p.Filtering = gene::graphics::FilteringOptions::Nearest;
		m_texture.Load("Data/grass.png", p);
	} 

    virtual void Tick(const gene::platform::GameTime& time) override {
    }
	
    virtual void Draw() override {
		m_2drenderer.Begin();
		//m_2drenderer.FillRectangle(m_object.Position, 100, 100, m_object.Colour);
		m_2drenderer.PushTransform(gene::Matrix4::Scale((4.f)));
		m_2drenderer.DrawTexture({0.f,32.f,0.f}, &m_texture);
		m_2drenderer.DrawTexture({ 16,32.f,0.f }, &m_texture);

		m_2drenderer.PopTransform();
		m_2drenderer.End();
		m_2drenderer.Present();
    }
      
    virtual void GuiDraw() override {
		using namespace gene;
		ImGui::Begin("Game Object Editor");
		gene::graphics::ImGuiHelpers::ReflectObject(&m_object);
		ImGui::End();
    }
};

int GeneMain(int argc, char **argv)
{
    gene::App* mapDemo = new ClearColorDemo();
    mapDemo->Run(1280, 720, "App Demo!");

    return 0;
}
