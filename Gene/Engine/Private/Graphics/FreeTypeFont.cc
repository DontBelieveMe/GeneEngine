#include <GeneCommon.h>
#include <algorithm>
#include "FreeTypeFont.h"

using namespace Gene::Graphics;

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

void FreeTypeTexture::CopyTextureToPos(int w, int h, Gene::byte *data, FT_GlyphSlot slot)
{
    const int padding = s_AtlasPadding;
    int xIndex = m_XIndex;
    int yIndex = m_YIndex;
    for (int y = 0; y < h; ++y)
    {
        byte *ourRow = m_Data + ((yIndex + y) * m_Width + xIndex) * s_AtlasDepth;
        byte *srcRow = data + (y * w);
        
        for (int x = 0; x < w; ++x)
        {
            ourRow[x * s_AtlasDepth] = 0xff;
            ourRow[x * s_AtlasDepth + 1] = srcRow[x];
        }
    }
    
    m_XIndex += slot->bitmap.width + padding;
    
    if (m_XIndex + slot->bitmap.width > m_Width)
    {
        m_YIndex += m_MaxHeight + padding;
        m_XIndex = padding;
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
    texture->Format    = Texture2D::PixelFormat::LuminanceAlpha;
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

    int yIndex = m_YIndex;
    int xIndex = m_XIndex;

    int padding = s_AtlasPadding;

    int atlasW = m_Width;
    int atlasH = m_Height;

    // TODO: Not sure if all of these casts are needed
    glyph.UV_TopLeft     = Vector2((float)xIndex / atlasW, (float)(yIndex) / atlasH);
    glyph.UV_TopRight    = Vector2((float)(xIndex + w) / atlasW, (float)(yIndex) / atlasH);
    glyph.UV_BottomLeft  = Vector2((float)xIndex / atlasW, (float)(yIndex + h + padding) / atlasH);
    glyph.UV_BottomRight = Vector2((float)(xIndex + w) / atlasW, (float)(yIndex + h + padding) / atlasH);
    
    glyph.Advance        = Vector2(static_cast<float>(slot->advance.x >> 6), static_cast<float>(slot->advance.y >> 6));
    glyph.Width          = w;
    glyph.Height         = h;
    glyph.Offset         = Vector2(static_cast<float>(slot->bitmap_left), static_cast<float>(slot->bitmap_top));

    return glyph;
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
            m_TallestGlyphSize = std::max(m_TallestGlyphSize, metrics.Height);
            m_Glyphs.insert(std::make_pair(charcode, metrics));
            m_Texture->CopyTextureToPos(bitmap.pitch, bitmap.rows, bitmap.buffer, slot);
        }
    }
}

Gene::Vector2 FreeTypeFont::GetKerning(char left, char right)
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
