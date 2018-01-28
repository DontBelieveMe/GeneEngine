#include <GeneUI/Application.hpp>

using namespace GeneUI;

void Application::Run(const std::unique_ptr<Window>& window)
{
    window->Show();

    Gene::Platform::Window *platformWindow = window->m_Window;
    while (platformWindow->Running())
    {
        platformWindow->PollEvents();
        platformWindow->Clear();
        window->m_Renderer->Begin();
        window->Redraw();
        window->m_Renderer->End();
        window->m_Renderer->Present();

        platformWindow->SwapBuffers();
    }
}