#include <Platform/Window.h>
#include <Graphics/Color.h>
#include <Graphics/Renderer2D.h>
#include <Platform/Time.h>
#include <Math/Math.h>
#include <Graphics/Buffer.h>
#include <Content/OBJModelLoader.h>
#include <Runtime/Application.h>
#include <Input/InputController.h>
#include <imgui/imgui.h>


class ClearColorDemo : public gene::App {
public:
    virtual void Init() override {
        GetWindow()->SetClearColor(gene::graphics::Color(79, 87, 99, 255));
    }

    virtual void Tick(const gene::platform::GameTime& time) override {
    }

    virtual void Draw() override {
    }

    virtual void GuiDraw() override {
        ImGui::ShowDemoWindow();
    }
};

int GeneMain(int argc, char **argv)
{
    gene::App* mapDemo = new ClearColorDemo();
    mapDemo->Run(1080, 720, "App Demo!");

    return 0;
}
