#if 1
#include <Platform/Window.h>
#include <Graphics/Color.h>
#include <Graphics/Renderer2D.h>
#include <Platform/Time.h>
#include <Math/Math.h>

int GeneMain(int argc, char **argv)
{
    using namespace gene::platform;
    using namespace gene;
    using namespace gene::graphics;
    using namespace gene::input;

    WindowInfo info;
    info.Width = 800;
    info.Height = 600;
    info.Title = "Hello World!";

    Window *window = Window::CreateWindow(info);
    window->Create();
    window->SetClearColor(Color(69, 76, 86, 255));

    GameTime time;
    time.Start();

    Renderer2D renderer;
    renderer.Init(Matrix4::Orthographic(window->Width(), 0.f, 0.f, window->Height(), 1.0f, -1.0f));

    float x = 75.0f;
    float y = 75.0f;
    Vector2 ballPosition;
    
    InputController *input = window->GetInputController();  
    MouseDevice *mouseDevice = input->GetMouseDevice();

    window->Show();
    while(window->Running()) {
        time.StartFrame();
        window->PollEvents();
        
        if (mouseDevice->IsButtonDown(MouseButton::Left)) {
            Vector2i mPos = mouseDevice->GetCursorPosition();

            Vector2 diff(mPos.X - x, mPos.Y - y);
            diff.Normalize();
			
            x += diff.X * 10.f;
            y += diff.Y * 10.f;
        }

        window->Clear();
        renderer.Begin();

        renderer.FillCircle({x,y}, 50, Color::Red, 32);
        
        renderer.End();
        renderer.Present();

        if (x-50 > window->Width()) 
        {
            x = -50;
        }

        window->SwapBuffers();
        time.EndFrame();
        time.Sleep(1000.f / 60.f);
    }

    return 0;
}

#endif
