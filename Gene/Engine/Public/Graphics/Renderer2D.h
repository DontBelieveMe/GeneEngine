#pragma once

#include <vector>
#include <Graphics/Renderable2D.h>

namespace Gene { namespace Graphics {
    class Renderer2D {
    public:
        ~Renderer2D();

        void Submit(Renderable2D *renderable);
    private:
        std::vector<Renderable2D*> m_Renderables;
    };
}}
