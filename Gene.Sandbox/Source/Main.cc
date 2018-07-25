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

class ClearColorDemo : public gene::App {
private:
    gene::graphics::Renderer2D m_renderer;
    gene::graphics::Color m_circleColor;
    gene::Vector2 m_position;
    int m_points = 5;

public:
    virtual void Init() override {
        auto win = GetWindow();

        GetWindow()->SetClearColor(gene::graphics::Color(79, 87, 99, 255));
        m_renderer.Init(gene::Matrix4::Orthographic(win->Width(), 0, 0, win->Height(), 100.f, 0.1f));

        m_position.Set(300);
    }

    virtual void Tick(const gene::platform::GameTime& time) override {
    }

    virtual void Draw() override {
        m_renderer.Begin();
        m_renderer.FillCircle(m_position, 150.f, m_circleColor, m_points);
        m_renderer.End();
        m_renderer.Present();
    }

    virtual void GuiDraw() override {
        using namespace gene::graphics;

        ImGui::Begin("Circle Controller");
        {
            ImGui::SliderInt("No. Points", &m_points, 3, 32);
            ImGuiHelpers::ColorPicker("Circle Color", &m_circleColor);
            ImGuiHelpers::InputVector2("Circle Position", &m_position);
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
