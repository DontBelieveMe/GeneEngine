#include <GeneUI/Window.hpp>
#include <GeneUI/Application.hpp>
#include <Windows.h>

class MyWindow : public GeneUI::Window
{
public:
};

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
    using namespace GeneUI;

    std::unique_ptr<Window> window = std::make_unique<MyWindow>();

    Application::Run(window);
}