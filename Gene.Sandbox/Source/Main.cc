#include <Platform/Window.h>
#include <Graphics/Color.h>
#include <Graphics/Renderer2D.h>
#include <Platform/Time.h>
#include <Math/Math.h>
#include <Graphics/Buffer.h>
#include <Content/OBJModelLoader.h>
#include <Runtime/Application.h>

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
