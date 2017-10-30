#pragma once

#include <Math/Vector2.h>

#include <Graphics/Renderer2D.h>
#include <Input/KeyboardState.h>

namespace Gene { namespace Graphics { namespace GUI { 
    class Widget {
    public:
        virtual void Draw(Renderer2D *renderer) = 0;
        virtual void KeyDown(Input::Key key) {}

        Vector2 Position;
        Vector2 Size;
    private:

    };
}}}