#include <Platform/Window.h>
#include <Graphics/Color.h>
#include <Graphics/Renderer2D.h>
#include <Platform/Time.h>
#include <Math/Math.h>
#include <Graphics/Buffer.h>
#include <Content/OBJModelLoader.h>

namespace gene {
    class App {
    public:
        App() : m_fps(60), m_window(nullptr) {}

        virtual void Tick(const platform::GameTime& time) {}
        virtual void Draw() {}

        virtual void Init() {}

        void Run(int windowW, int windowH, const char *title) {
            platform::WindowInfo info;
            info.Width = windowW;
            info.Height = windowH;
            info.Title = title;

            m_window = platform::Window::CreateWindow(info);
            m_window->Create();
            m_window->SetClearColor(graphics::Color::Black);

            Init();

            platform::GameTime gameTimer;
            m_window->Show();
            while (m_window->Running())
            {
                gameTimer.StartFrame();
                m_window->PollEvents();

                Tick(gameTimer);

                m_window->Clear();
                Draw();
                m_window->SwapBuffers();

                gameTimer.EndFrame();

                if (m_fps > 0)
                {
                    gameTimer.Sleep(1000.0f / m_fps);
                }
            }
        }

    protected:
        platform::Window *GetWindow() { return m_window; }
        void SetTargetFPS(float fps) { m_fps = fps; }
        float GetTargetFPS(float fps) { return m_fps; }

    private:
        platform::Window *m_window;

        float m_fps;
    };
}

class ClearColorDemo : public gene::App {
private:
    gene::graphics::Color m_clearColor;

public:
    virtual void Tick(const gene::platform::GameTime& time) override {
        using namespace gene;
        using namespace gene::graphics;

        const float dampening = 400.0f;
        const float t = time.RunningTimeMilliseconds() / dampening;

        const float cosT = Maths::Cos(t);

        int r = (int)Maths::Map(cosT, -1.0f, 1.0f, 0, 255);
        int g = (int)Maths::Map(-cosT, -1.0f, 1.0f, 0, 255);

        m_clearColor = Color(r, g, r, 255);
    }

    virtual void Draw() override {
        GetWindow()->SetClearColor(m_clearColor);
    }
};

int GeneMain(int argc, char **argv)
{
    gene::App* mapDemo = new ClearColorDemo();
    mapDemo->Run(600, 400, "App Demo!");

    return 0;
}
