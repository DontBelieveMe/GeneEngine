// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include "FreeTypeFont.h"

#include <GeneCommon.h>
#include <algorithm>

using namespace gene::graphics;
using namespace gene;

const int s_AtlasDepth = 2;
const int s_AtlasPadding = 1;

/*
TODO:
    - Maybe?
    - Optimal packing algorithm
        -> Will decide where there is the the most optimal to place glyphs
        -> E.G place `.` `,` `'` etc on top of each other etc...
    - Also investigate glyph vertex instancing.
*/

FreeTypeTexture::FreeTypeTexture(int w, int h)
    : m_Width(w), m_Height(h), m_XIndex(s_AtlasPadding), m_YIndex(s_AtlasPadding), m_MaxHeight(0)
{
    // TODO:
    // Maybe we can shrink the texture afterwards if there is space available
    // However that would screw up the generated UVs
    // maybe store pixel coords first then generate UVs in second pass?/afterwards
    // EDIT: Instead of shrinking texture here is a potential algorithm.
    //          -> PASS 1 -> Calculate the potential height of the texture with all glyphs
    //          -> Round that height up to the nearest power of 2 & set texture to that size.
    //          -> PASS 2 -> Go through and pack all glyphs into texture as normal.
    m_Data = new byte[w * h * s_AtlasDepth];
    memset(m_Data, 0, w * h * s_AtlasDepth);
}

FreeTypeTexture::~FreeTypeTexture()
{
    delete[] m_Data;
}

FreeTypeGlyph FreeTypeTexture::CopyGlyphToTexture(FT_GlyphSlot slot)
{
	const int padding = s_AtlasPadding;
	
	int w = slot->bitmap.pitch;
	int h = slot->bitmap.rows;

	byte *data = slot->bitmap.buffer;

	if (m_XIndex + slot->bitmap.width > m_Width)
	{
		m_YIndex += m_MaxHeight + padding * 2;
		m_XIndex = padding;
		m_MaxHeight = 0;
	}

	int xIndex = m_XIndex;
	int yIndex = m_YIndex;

	SetRegion(xIndex, yIndex, slot->bitmap.pitch, slot->bitmap.rows, data);

	int atlasW = m_Width;
	int atlasH = m_Height;

	FT_Glyph_Metrics metrics = slot->metrics;

	FT_Pos metricW = metrics.width >> 6;
	FT_Pos metricH = metrics.height >> 6;

	FreeTypeGlyph glyph;
	SetGlyphsUVs(xIndex - padding, yIndex - padding, w + padding, h + padding, &glyph);

	glyph.Advance = Vector2(slot->advance.x / 64.f, static_cast<float>(slot->advance.y >> 6));
	glyph.Width = metricW;
	glyph.Height = metricH;
	glyph.Offset = Vector2(static_cast<float>(slot->bitmap_left), static_cast<float>(slot->bitmap_top));

	m_XIndex += slot->bitmap.width + padding*2;

	m_MaxHeight = std::max(m_MaxHeight, (int)metricH);

	return glyph;
}

void FreeTypeTexture::SetGlyphsUVs(int x, int y, int w, int h, FreeTypeGlyph *glyph)
{
	int atlasW = m_Width;
	int atlasH = m_Height;

	float fx = static_cast<float>(x);
	float fy = static_cast<float>(y);

	glyph->UV_TopLeft     = Vector2(fx / atlasW, fy / atlasH);
	glyph->UV_TopRight    = Vector2((fx + w) / atlasW, fy / atlasH);
	glyph->UV_BottomLeft  = Vector2(fx / atlasW, (fy + h) / atlasH);
	glyph->UV_BottomRight = Vector2((fx + w) / atlasW, (fy + h) / atlasH);
}

void FreeTypeTexture::SetRegion(int x, int y, int w, int h, byte *data)
{
	for (int yy = 0; yy < h; ++yy)
	{
		byte *ourRow = m_Data + ((y + yy) * m_Width + x) * s_AtlasDepth;
		byte *srcRow = data + (yy * w);

		for (int xx = 0; xx < w; ++xx)
		{
			ourRow[xx * s_AtlasDepth] = 0xff;
			ourRow[xx * s_AtlasDepth + 1] = srcRow[xx];
		}
	}
}

// TODO:
// Implement this: Currently it is possible for not all characters to fit on the texture
// If the font is too big or the texture atlas is too small.
// Correct behaviour -> Only load enough characters that will fit on the texture whole.
bool FreeTypeTexture::IsEnoughSpaceForCharacter(int glyphHeight)
{
    return m_YIndex + glyphHeight < m_Height;
}

Texture2D *FreeTypeTexture::GenerateTexture()
{
    Texture2D *texture = new Texture2D();

    TextureParameters params;
    params.Filtering = FilteringOptions::Linear;
    params.Format    = PixelFormat::LuminanceAlpha;

    texture->Parameters = params;

    texture->Load(m_Data, m_Width, m_Height, s_AtlasDepth);
    return texture;
}

FreeTypeFont::FreeTypeFont(const char *path, float size) 
    : m_TallestGlyphSize(0)
{
    m_Texture = new FreeTypeTexture(512, 512);

    FT_Error error;
    FT_Library library;
    
    error = FT_Init_FreeType(&library);
    error = FT_New_Face(library, path, 0, &m_Face);

    GE_ASSERT(error != FT_Err_Unknown_File_Format, "Font has unknown file format");
    
    error = FT_Set_Char_Size(m_Face, static_cast<FT_F26Dot6>(size * 64.f), 0, 300, 300);
    
    GE_ASSERT(!error, "FreeTypeFont::FreeTypeFont(...) Cannot set freetype font char size");
}

FreeTypeFont::~FreeTypeFont()
{
    delete m_Texture;
}

Texture2D *FreeTypeFont::GenerateTexture()
{
    return m_Texture->GenerateTexture();
}

void FreeTypeFont::LoadCharacter(char charcode)
{
    FT_UInt index = FT_Get_Char_Index(m_Face, charcode);

	if (index <= 0)
	{
		LOG(LogLevel::Warning, "Unidentified charcode: '", charcode, "'. Aborting load!");
		return;
	}

    FT_Load_Glyph(m_Face, index, FT_LOAD_DEFAULT);
    FT_Render_Glyph(m_Face->glyph, FT_RENDER_MODE_NORMAL);

    FT_GlyphSlot slot = m_Face->glyph;
    FT_Bitmap bitmap = slot->bitmap;
    
    if (m_Texture->IsEnoughSpaceForCharacter(bitmap.rows))
    {
        std::unordered_map<char, FreeTypeGlyph>::iterator it = m_Glyphs.find(charcode);
        if (it == m_Glyphs.end())
        {
			FreeTypeGlyph metrics = m_Texture->CopyGlyphToTexture(slot);
            m_TallestGlyphSize = std::max(m_TallestGlyphSize, metrics.Height);
            m_Glyphs.insert(std::make_pair(charcode, metrics));
        }
    }
}

Vector2 FreeTypeFont::GetKerning(char left, char right)
{
    FT_UInt leftIndex = FT_Get_Char_Index(m_Face, left);
    FT_UInt rightIndex = FT_Get_Char_Index(m_Face, right);

    FT_Vector kerning;
    FT_Get_Kerning(m_Face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &kerning);
    return Vector2(kerning.x / 64.f, kerning.y / 64.f);
}

FreeTypeGlyph *FreeTypeFont::GetGlyph(char charcode)
{
    std::unordered_map<char, FreeTypeGlyph>::iterator it = m_Glyphs.find(charcode);
    return it == m_Glyphs.end() ? nullptr : &((*it).second);
}
