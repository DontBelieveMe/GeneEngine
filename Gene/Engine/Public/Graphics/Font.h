// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Graphics/Texture2D.h>
#include <Math/Vector2.h>
#include <Core/String.h>
#include <Runtime/Resources.h>

#include "../../Private/Graphics/FreeTypeFont.h"

namespace gene { 
    namespace graphics {
        class Font : public IResource
        {
        public:
            static const float DEFAULT_SIZE;

        public:
            /** Creates a font object from the font file specified, and if a size is not explictly specified a size of 11px */
            Font(const char *fontFile, float size = DEFAULT_SIZE);
            Font();

            /** Creates a font object from the font file specified, and if a size is not explictly specified a size of 11px */
            void Load(const char *fontFile, float size = DEFAULT_SIZE);

            virtual void Destroy();

            /** Destroys any resources used by the font */
            ~Font();

            /** Return the size of the font as specified on construction */
            inline float		   Size()	   const { return m_Size; }

            /** Return the fonts OpenGL texture object */
            Texture2D			  *GLTexture() { return m_Texture; }

            /** Return the total dimensions of the string taking into account newlines */
            Vector2                MeasureString(const String& str);

            /** Calculate the dimensions of each line of a string. If the string has no newlines then the resultant array contains the dimensions for that string */
            Array<Vector2>         MeasureLines(const String& str);

            /** Get the underlying FreeTypeFont handle. Holds glyph data. */
            FreeTypeFont          *GetFreeTypeFont() { return m_FreeTypeFont; }

        private:
            FreeTypeFont          *m_FreeTypeFont;
            Texture2D			  *m_Texture;

            float				   m_Size;
        };
    }
}
