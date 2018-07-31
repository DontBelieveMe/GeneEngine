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

#include <filesystem>
#include <Runtime/Reflection.h>

gene::platform::Window* _window;

namespace lapi 
{
    bool ImGuiButton(const char* buttonText)
    {
        return ImGui::Button(buttonText);
    }

    void ImGuiText(const char* text)
    {
        ImGui::Text(text);
    }
}

class ClearColorDemo : public gene::App {

public:
    gene::scripting::LuaEnvironment env;  
    gene::Vector2 m_Position;

    virtual void Init() override { 
        using namespace gene;

        platform::Window *window = GetWindow();
        _window = window;
        window->SetClearColor(gene::graphics::Color(79, 87, 99, 255));
        LOG(LogLevel::Warning, "", META_GET_DATA(gene::Vector2));
    } 

    virtual void Tick(const gene::platform::GameTime& time) override {
    }

    virtual void Draw() override {
    }
      
    virtual void GuiDraw() override {
    }
};

int GeneMain(int argc, char **argv)
{
    gene::App* mapDemo = new ClearColorDemo();
    mapDemo->Run(1280, 720, "App Demo!");

    return 0;
}
