#if 1
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
        virtual void Step(const platform::GameTime& time);
        virtual void Init();

        void Run(int windowW, int windowH, const char *title) {
            platform::WindowInfo info;
            info.Width = windowW;
            info.Height = windowH;
            info.Title = title;

            m_window = platform::Window::CreateWindow(info);
            m_window->Create();

        }

    private:
        platform::Window *m_window;
    };
}


int GeneMain(int argc, char **argv)
{
    using namespace gene::platform;
    using namespace gene;
    using namespace gene::graphics;
    using namespace gene::input;
    using namespace gene::runtime;

    WindowInfo info;
    info.Width = 800;
    info.Height = 600;
    info.Title = "Hello World!";

    Window *window = Window::CreateWindow(info);
    window->Create();
    window->SetClearColor(Color(69, 76, 86, 255));

    GameTime time;
    time.Start();

    OBJModelLoader modelLoader;
    GeneModel* model = modelLoader.Load("Data/doughnut.obj");

    Buffer vertexBuff(Buffer::Type::ArrayBuffer);
    Buffer textureBuff(Buffer::Type::ArrayBuffer);
    Buffer indexBuff(Buffer::Type::ElementBuffer);

    BufferDescriptor vertexBuffDesc;
    vertexBuffDesc.Data = model->Vertices.data();
    vertexBuffDesc.DataType = opengl::GLType::Float;
    vertexBuffDesc.DrawType = BufferDrawType::Static;
    vertexBuffDesc.Size = model->Vertices.size() * 3 * 4;
    vertexBuff.SetData(vertexBuffDesc);

    BufferDescriptor textureBuffDesc;
    textureBuffDesc.Data = model->UVs.data();
    textureBuffDesc.DataType = opengl::GLType::Float;
    textureBuffDesc.DrawType = BufferDrawType::Static;
    textureBuffDesc.Size = model->Vertices.size() * 2 * 4;
    textureBuff.SetData(textureBuffDesc);

    BufferDescriptor indexBufferDesc;
    indexBufferDesc.Data = model->Indices.data();
    indexBufferDesc.DataType = opengl::GLType::Float;
    indexBufferDesc.DrawType = BufferDrawType::Static;
    indexBufferDesc.Size = model->Indices.size() * 3 * 4;
    indexBuff.SetData(indexBufferDesc);

    AttributeDescriptor vertexAttribDesc;
    vertexAttribDesc.ByteOfffset = 0;
    vertexAttribDesc.Index = 0;
    vertexAttribDesc.Stride = sizeof(Vector3);
    vertexAttribDesc.ComponentCount = 3;

    AttributeDescriptor textureAttribDesc;
    textureAttribDesc.Index = 2;
    textureAttribDesc.ByteOfffset = 0;
    textureAttribDesc.Stride = sizeof(Vector2);
    textureAttribDesc.ComponentCount = 3;

    VertexArray vao;

    window->Show();
    while(window->Running()) {
        time.StartFrame();
        window->PollEvents();
        
        
        window->SwapBuffers();
        time.EndFrame();
        time.Sleep(1000.f / 60.f);
    }

    return 0;
}

#endif
