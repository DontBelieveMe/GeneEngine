#pragma once

#include <Math/Vector2.h>

#include <Graphics/Font.h>
#include <Graphics/Color.h>

#include <string>

namespace Gene { namespace Graphics {
    
    class Renderer2D
    {
    public:
        void DrawString(const Font& font, const std::string& text, const Math::Vector2& pos, const Graphics::Color = Graphics::Color::Black);
    };
}}
