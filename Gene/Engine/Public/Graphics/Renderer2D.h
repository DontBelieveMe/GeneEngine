#pragma once

#include <Math/Vector2.h>
#include <Graphics/Font.h>

#include <string>

namespace Gene { namespace Graphics {
    class Sprite {
    public:
        Math::Vector2 Position;

    };

    class Renderer2D
    {
    public:
        void DrawString(const Font& font, const std::string& text);
    };
}}
