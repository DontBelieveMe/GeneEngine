#include <GeneUI/Window.hpp>

using namespace GeneUI;

Window::Window()
{
    m_Window = Gene::Platform::Window::CreateWindow({ 800,600, "Hello From GeneUI!", false });
    m_Window->CreateGLContext();
    m_Window->Create();

    m_Renderer = std::make_unique<Gene::Graphics::Renderer2D>();
    m_Renderer->Init(Gene::Matrix4::Orthographic(800, 0, 0, 600, 1.0f, -1.0f));
}

void Window::Show()
{
    m_Window->Show();
}

void Window::Redraw()
{
    m_Renderer->FillRectangle({ 100, 100 }, 100, 100, Gene::Graphics::Color::Red);
}