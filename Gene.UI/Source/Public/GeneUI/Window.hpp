#pragma once

#include <Platform/Window.h>
#include <Graphics/Renderer2D.h>
#include <memory>

namespace GeneUI {
    class Application;

    class Window {
        friend class Application;

    private:
        Gene::Platform::Window *m_Window;
        std::unique_ptr<Gene::Graphics::Renderer2D> m_Renderer;

    public:
        Window();

        void Show();
        void Redraw();
    };
};
