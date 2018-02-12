#pragma once

#include <Graphics/Texture2D.h>
#include <Math/Vector2.h>

#include "../../Private/Graphics/FreeTypeFont.h"

namespace ftgl {
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace Gene { namespace Graphics {
	class Font 
	{
	public:
		static const float DEFAULT_SIZE;

	public:
		Font(const char *fontFile, float size = DEFAULT_SIZE);
		~Font();

		inline float		   Size()	   const { return m_Size; }
		ftgl::texture_font_t  *TextureFont()		 { return m_Font; }
		Texture2D			  *GLTexture()		 { return m_Texture; }
        Vector2                MeasureString(const std::string& str);
        FreeTypeFont          *GetFreeTypeFont() { return m_FreeTypeFont; }

	private:
        FreeTypeFont          *m_FreeTypeFont;
		Texture2D			  *m_Texture;
		ftgl::texture_atlas_t *m_Atlas;
		ftgl::texture_font_t  *m_Font;

		float				   m_Size;
	};
}}