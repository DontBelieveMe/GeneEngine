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
    
    virtual void Init() override { 
        using namespace gene;

        platform::Window *window = GetWindow();
        _window = window;
        window->SetClearColor(gene::graphics::Color(79, 87, 99, 255));

        env.LoadFile("Data/test.lua");
         
        /*lua_newtable(env.GetState());
        lua_pushstring(env.GetState(), "a");
        lua_pushnumber(env.GetState(), 123);
        lua_settable(env.GetState(), -3);
        lua_setglobal(env.GetState(), "mytable");*/

        // TODO: This works but only in a flat way -> We need to make it recursive.
        /*
        Variant table = {
            { "key", "value" },
            { "health", 512 },
            { "nestedTable", {
                { "anotherKey", false },
            }}
        };

        std::initalizer_list?
        */
        gene::scripting::LuaTable *table = env.CreateTable("aTable");
        table->AddPair("key", 512);
        
        env.Register("ImGuiText", &lapi::ImGuiText); 
        env.Register("ImGuiButton", &lapi::ImGuiButton);
    } 

    virtual void Tick(const gene::platform::GameTime& time) override {
    }

    virtual void Draw() override {
    }
      
    virtual void GuiDraw() override {
        env.Call("guiDraw");
    }
};

int GeneMain(int argc, char **argv)
{
    meta::DefaultRegistrations();
    LOG(gene::LogLevel::Infomation, "", META_GET_DATA(gene::Vector2));

    gene::App* mapDemo = new ClearColorDemo();
    mapDemo->Run(1280, 720, "App Demo!");

    return 0;
}
