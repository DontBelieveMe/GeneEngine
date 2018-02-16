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
    
    for(char c = ' '; c <= '~'; ++c) {
        m_FreeTypeFont->LoadCharacter(c);
    }
	
    m_Texture = m_FreeTypeFont->GenerateTexture();
}

Font::~Font() 
{
	delete m_Texture;
    delete m_FreeTypeFont;
}

Vector2 Font::MeasureString(const std::string & str)
{
    float width = 0.0f;
    float height = 0.0f;

    int i = 0;
    for (char character : str) {
        if (character == '\n')continue;
        
        FreeTypeGlyph *glyph = m_FreeTypeFont->GetGlyph(character);

		if (!glyph)
		{
			LOG(LogLevel::Warning, "Cannot measure size of character '", character, "'. Aborting measure for this character and moving on!");
			continue;
		}

        if (i > 0)
        {
            Vector2 kerning = m_FreeTypeFont->GetKerning(str[i - 1], str[i]);
            width += kerning.X;
        }

        width += glyph->Advance.X;

        if (glyph->Height > height)
        {
            height = static_cast<float>(glyph->Height);
        }

        i++;
    }

    return Vector2(width, height);
}
