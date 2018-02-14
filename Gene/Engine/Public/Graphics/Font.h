#pragma once

#include <Graphics/Texture2D.h>
#include <Math/Vector2.h>

#include "../../Private/Graphics/FreeTypeFont.h"

namespace Gene { namespace Graphics {
	class Font 
	{
	public:
		static const float DEFAULT_SIZE;

	public:
        /** Creates a font object from the font file specified, and if a size is not explictly specified a size of 11px */
		Font(const char *fontFile, float size = DEFAULT_SIZE);

        /** Destroys any resources used by the font */
		~Font();

        /** Return the size of the font as specified on construction */
		inline float		   Size()	   const { return m_Size; }

        /** Return the fonts OpenGL texture object */
		Texture2D			  *GLTexture()		 { return m_Texture; }

        /** Return the dimensions of the string where the Width = X component and Height = Y Component */
        Vector2                MeasureString(const std::string& str);

        /** Get the underlying FreeTypeFont handle. Holds glyph data. */
        FreeTypeFont          *GetFreeTypeFont() { return m_FreeTypeFont; }

	private:
        FreeTypeFont          *m_FreeTypeFont;
		Texture2D			  *m_Texture;

		float				   m_Size;
	};
}}
