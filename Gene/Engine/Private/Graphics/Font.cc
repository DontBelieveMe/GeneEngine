#include "FreetypeGL.h"

#include <Graphics/Font.h>
#include <iostream>
#include <IO/File.h>

#include <Platform/OpenGL.h>

#include "FreeTypeFont.h"

using namespace Gene::Graphics;
using namespace Gene;

const float Font::DEFAULT_SIZE = 11.f;

Font::Font(const char *fontFile, float size): m_Size(size)
{
    m_FreeTypeFont = new FreeTypeFont(fontFile, size);
    
    for(char c = '!'; c <= '~'; ++c) {
        m_FreeTypeFont->LoadCharacter(c);
    }
    m_FreeTypeFont->LoadCharacter(' ');
    m_Texture = m_FreeTypeFont->GenerateTexture();
}

Font::~Font() 
{
	delete m_Texture;
}

Vector2 Font::MeasureString(const std::string & str)
{
    float width = 0.0f;
    float height = 0.0f;

    for (char character : str) {
        ftgl::texture_glyph_t *glyph = ftgl::texture_font_get_glyph(m_Font, &character);
        width += glyph->advance_x;
        if (glyph->advance_y > height) {
            height = glyph->advance_y;
        }
    }

    return Vector2(width, height);
}
