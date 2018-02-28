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
#include <Input/Keyboard.h>

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

    Renderer2D renderer;
    renderer.Init(Matrix4::Orthographic(info.Width, 0, 0, info.Height, 1.0f, -1.0f));

    window->Show();
    GameTime gameTime;
    gameTime.Init();
    while (window->Running())
    {
        gameTime.StartFrame();

      
        // 2D rendering code
        {
            renderer.Begin();
            renderer.FillRectangle({ 10, 10 }, 100, 100, Gene::Graphics::Color::Red);
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