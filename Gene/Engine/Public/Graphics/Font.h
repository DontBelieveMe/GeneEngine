#pragma once

#include <Graphics/Texture2D.h>

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

		inline float Size() const { return m_Size; }

	private:
		Texture2D			  *m_Texture;
		ftgl::texture_atlas_t *m_Atlas;
		ftgl::texture_font_t  *m_Font;

		float				   m_Size;
	};
}}