#include <GeneCommon.h>
#include <algorithm>
#include "FreeTypeFont.h"

using namespace Gene::Graphics;

const int s_AtlasDepth = 2;

/*
TODO:
    - Maybe?
    - Optimal packing algorithm
        -> Will decide where there is the the most optimal to place glyphs
        -> E.G place `.` `,` `'` etc on top of each other etc...
*/

FreeTypeTexture::FreeTypeTexture(int w, int h)
    : m_Width(w), m_Height(h), m_XIndex(0), m_YIndex(0), m_MaxHeight(0)
{
    // TODO:
    // Maybe we can shrink the texture afterwards if there is space available
    // However that would screw up the generated UVs
    // maybe store pixel coords first then generate UVs in second pass?/afterwards
    m_Data = new byte[w * h * s_AtlasDepth];
    memset(m_Data, 0, w * h * s_AtlasDepth);
}

FreeTypeTexture::~FreeTypeTexture()
{
    delete[] m_Data;
}

void FreeTypeTexture::CopyTextureToPos(int w, int h, Gene::byte *data)
{
    const int padding = 2;

    for (int y = 0; y < h; ++y)
    {
        byte *ourRow = m_Data + ((m_YIndex + y) * m_Width + m_XIndex) * s_AtlasDepth;
        byte *srcRow = data + (y * w);
        
        for (int x = 0; x < w; ++x)
        {
            ourRow[x * s_AtlasDepth] = 0xff;
            ourRow[x * s_AtlasDepth + 1] = srcRow[x];
        }
    }

    m_XIndex += w + padding;
    
    if (m_XIndex + w > m_Width) 
    {
        m_YIndex += m_MaxHeight + padding;
        m_XIndex = 0;
        m_MaxHeight = 0;
    }

    m_MaxHeight = std::max(m_MaxHeight, h);
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
    texture->Format = Texture2D::PixelFormat::LuminanceAlpha;
    texture->Filtering = Texture2D::FilteringOptions::Nearest;
    texture->Load(m_Data, m_Width, m_Height, s_AtlasDepth);
    return texture;
}

FreeTypeGlyph FreeTypeTexture::GetGlyphUVs(FT_GlyphSlot slot)
{
    FT_Glyph_Metrics metrics = slot->metrics;

    FT_Pos w = metrics.width >> 6;
    FT_Pos h = metrics.height >> 6;

    FreeTypeGlyph glyph;

    // TODO: Not sure if all of these casts are needed
    glyph.UV_TopLeft     = Vector2((float)m_XIndex / m_Width, (float)m_YIndex / m_Height);
    glyph.UV_TopRight    = Vector2((float)(m_XIndex + w) / m_Width, (float)m_YIndex / m_Height);
    glyph.UV_BottomLeft  = Vector2((float)m_XIndex / m_Width, (float)(m_YIndex + h) / m_Height);
    glyph.UV_BottomRight = Vector2((float)(m_XIndex + w) / m_Width, (float)(m_YIndex + h) / m_Height);
    
    glyph.Advance        = Vector2(slot->advance.x >> 6, slot->advance.y >> 6);
    glyph.Width          = w;
    glyph.Height         = h;
    glyph.Offset         = Vector2(slot->bitmap_left, slot->bitmap_top);

    return glyph;
}

FreeTypeFont::FreeTypeFont(const char *path, float size) 
{
    m_Texture = new FreeTypeTexture(512, 512);

    FT_Error error;
    FT_Library library;
    
    error = FT_Init_FreeType(&library);
    error = FT_New_Face(library, path, 0, &m_Face);

    GE_ASSERT(error != FT_Err_Unknown_File_Format, "Font has unknown file format");
    
    error = FT_Set_Char_Size(m_Face, size * 64.f, 0, 300, 300);
    
    GE_ASSERT(!error);
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

    FT_Load_Glyph(m_Face, index, FT_LOAD_DEFAULT);
    FT_Render_Glyph(m_Face->glyph, FT_RENDER_MODE_NORMAL);

    FT_GlyphSlot slot = m_Face->glyph;
    FT_Bitmap bitmap = slot->bitmap;

    if (m_Texture->IsEnoughSpaceForCharacter(bitmap.rows))
    {
        std::unordered_map<char, FreeTypeGlyph>::iterator it = m_Glyphs.find(charcode);
        if (it == m_Glyphs.end())
        {
            FreeTypeGlyph metrics = m_Texture->GetGlyphUVs(slot);         
            m_Glyphs.insert(std::make_pair(charcode, metrics));
            m_Texture->CopyTextureToPos(bitmap.pitch, bitmap.rows, bitmap.buffer);
        }
    }
}

Gene::Vector2 FreeTypeFont::GetKerning(char left, char right)
{
    FT_Vector kerning;
    FT_Get_Kerning(m_Face, left, right, FT_KERNING_DEFAULT, &kerning);
    return Vector2(kerning.x / 64.f, kerning.y / 64.f);
}

FreeTypeGlyph *FreeTypeFont::GetGlyph(char charcode)
{
    std::unordered_map<char, FreeTypeGlyph>::iterator it = m_Glyphs.find(charcode);
    return it == m_Glyphs.end() ? nullptr : &((*it).second);
}