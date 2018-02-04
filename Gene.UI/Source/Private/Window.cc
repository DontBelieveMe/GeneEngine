#include <GeneUI/Window.hpp>
#include <Graphics/Font.h>

using namespace GeneUI;
Gene::Graphics::Font *_font;

Window::Window()
{
    m_Window = Gene::Platform::Window::CreateWindow({ 800,600, "Hello From GeneUI!", false });
    m_Window->Create();
    m_Window->CreateGLContext();

    m_Renderer = std::make_unique<Gene::Graphics::Renderer2D>();
    m_Renderer->Init(Gene::Matrix4::Orthographic(800, 0, 0, 600, 1.0f, -1.0f));
    _font = new Gene::Graphics::Font("Data/Gidole-Regular.ttf", 30);
}

void Window::Show()
{
    m_Window->Show();
}

void Window::Redraw()
{
    m_Renderer->FillRectangle({ 100, 100 }, 120, 100, Gene::Graphics::Color::Red);
    m_Renderer->DrawString(_font, "Hello World", { 110, 140 }, Gene::Graphics::Color::White);
}