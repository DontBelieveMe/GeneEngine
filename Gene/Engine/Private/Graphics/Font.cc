// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Graphics/Font.h>
#include <iostream>
#include <IO/File.h>

#include <Platform/OpenGL.h>
#include <Core/Array.h>

#include <algorithm>

#include "FreeTypeFont.h"

using namespace gene::graphics;
using namespace gene;

const float Font::DEFAULT_SIZE = 11.f;

Font::Font(const char *fontFile, float size)
{
    Load(fontFile, size);
}

void Font::Load(const char *fontFile, float size)
{
    m_Size = size;
    m_FreeTypeFont = new FreeTypeFont(fontFile, size);

    for (char c = ' '; c <= '~'; ++c) {
        m_FreeTypeFont->LoadCharacter(c);
    }

    m_Texture = m_FreeTypeFont->GenerateTexture();
}

Font::Font() {}

void Font::Destroy()
{
    delete m_Texture;
    delete m_FreeTypeFont;
}

Font::~Font() 
{

}

Array<Vector2> Font::MeasureLines(const String& str)
{
    Vector2 currentLine;

    Array<Vector2> lines;

    int i = 0;
    for (char character : str)
    {
         if (character == '\n')
        {
            lines.push_back(currentLine);
            currentLine = Vector2();

            continue;
        }
        
        FreeTypeGlyph *glyph = m_FreeTypeFont->GetGlyph(character);

		if (!glyph)
		{
			LOG(LogLevel::Warning, "Cannot measure size of character '", character, "'. Aborting measure for this character and moving on!");
			continue;
		}

        if (i > 0)
        {
            Vector2 kerning = m_FreeTypeFont->GetKerning(str[i - 1], str[i]);
            currentLine.X += kerning.X;
        }

        currentLine.X += glyph->Advance.X;

        if (glyph->Height > currentLine.Y)
        {
            currentLine.Y = static_cast<float>(glyph->Height);
        }

        i++;
    }
    lines.push_back(currentLine);

    return lines;
}

Vector2 Font::MeasureString(const String& str)
{
    Array<Vector2> lines = MeasureLines(str);

    Vector2 totalSize;

    for (const Vector2& vec2 : lines)
    {
        if (vec2.X > totalSize.X) 
        {
            totalSize.X = vec2.X;
        }

        if (vec2.Y > totalSize.Y)
        {
            totalSize.Y = vec2.Y;
        }
    }

    return totalSize;
}
