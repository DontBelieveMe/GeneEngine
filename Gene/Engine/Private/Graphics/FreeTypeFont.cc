#include <GeneCommon.h>
#include <algorithm>
#include "FreeTypeFont.h"

using namespace Gene::Graphics;

FreeTypeTexture::FreeTypeTexture(int w, int h)
    : m_Width(w), m_Height(h), m_XIndex(0), m_YIndex(0), m_MaxHeight(0)
{
    m_Data = new byte[w * h];
    memset(m_Data, 0, w * h);
}

void FreeTypeTexture::CopyTextureToPos(int w, int h, Gene::byte *data)
{
    if (m_XIndex + w > m_Width) 
    {
        m_YIndex += m_MaxHeight;
        m_XIndex = 0;
        m_MaxHeight = 0;
    }

    for (int x = m_XIndex; x < m_XIndex + w; ++x)
    {
        for (int y = m_YIndex; y < m_YIndex + h; ++y)
        {
            m_Data[x + y * m_Width] = data[(x - m_XIndex) + (y - m_YIndex) * w];
        }
    }
    
    m_XIndex += w;
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
    texture->Format = Texture2D::PixelFormat::Red;
    texture->Filtering = Texture2D::FilteringOptions::Linear;
    texture->Load(m_Data, m_Width, m_Height);
    return texture;
}

FreeTypeGlyph FreeTypeTexture::GetGlyphUVs(FT_GlyphSlot slot)
{
    // TODO: Implement
    return {};
}

FreeTypeFont::FreeTypeFont(const char *path, float size) 
{
    m_Texture = new FreeTypeTexture(512, 512);
    int error;
    FT_Library library;
    error = FT_Init_FreeType(&library);
    error = FT_New_Face(library, path, 0, &m_Face);

    GE_ASSERT(error != FT_Err_Unknown_File_Format, "Font has unknown file format");
    
    error = FT_Set_Char_Size(m_Face, size * 64.f, 0, 300, 300);
}

Texture2D *FreeTypeFont::GenerateTexture()
{
    return m_Texture->GenerateTexture();
}

void FreeTypeFont::LoadCharacter(char charcode)
{
    int index = FT_Get_Char_Index(m_Face, charcode);
    FT_Load_Glyph(m_Face, index, FT_LOAD_DEFAULT);
    FT_Render_Glyph(m_Face->glyph, FT_RENDER_MODE_NORMAL);
    FT_GlyphSlot slot = m_Face->glyph;
    auto bitmap = slot->bitmap;

    if (m_Texture->IsEnoughSpaceForCharacter(bitmap.rows))
    {
        m_Texture->CopyTextureToPos(bitmap.pitch, bitmap.rows, bitmap.buffer);

        std::unordered_map<char, FreeTypeGlyph>::iterator it = m_Glyphs.find(charcode);
        if (it != m_Glyphs.end())
        {
            m_Glyphs.insert(std::make_pair(charcode, m_Texture->GetGlyphUVs(slot)));
        }
    }
}
