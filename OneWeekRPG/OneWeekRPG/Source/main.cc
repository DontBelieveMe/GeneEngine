#include <Platform/Window.h>
#include <Graphics/Renderer2D.h>
#include <GeneUseAll.h>

#include "cGlobals.h"

int main()
{
    WindowInfo info;
    info.Width = 800;
    info.Height = 600;
    info.Title = "One week RPG";

    Window *window = Window::CreateWindow(info);
    window->Create();
    window->CreateGLContext();
    window->SetClearColor(Color::Black);

    Renderer2D *renderer = new Renderer2D;
    renderer->Init(Matrix4::Orthographic(info.Width, 0, 0, info.Height, 1.0f, -1.0f));

    window->Show();
    while (window->Running())
    {
        window->PollEvents();
        window->Clear();
        renderer->Begin();
        
        renderer->End();
        renderer->Present();
        window->SwapBuffers();
    }
}