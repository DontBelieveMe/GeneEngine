#pragma once

#pragma once

#include <Graphics/GUI/Widget.h>
#include <Graphics/Font.h>

#include <string>

namespace Gene { namespace Graphics { namespace GUI { 
    class TextBox : public Widget {
    public:
        TextBox(Font *font);

        virtual void Draw(Renderer2D *renderer);
        virtual void KeyDown(Input::Keys key);

        Font *TextFont;
        std::string Text;
    };
}}}