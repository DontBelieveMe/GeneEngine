#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GeneCommon.h>
#include <Graphics/Texture2D.h>
#include <unordered_map>

namespace Gene { namespace Graphics {
    struct FreeTypeGlyph {
        int UV_TopLeft, UV_TopRight;
        int UV_BottomLeft, UV_BottomRight;
    };

    class FreeTypeTexture {
    public:
        FreeTypeTexture(int w, int h);

        void CopyTextureToPos(int w, int h, byte *data);
        byte *GetData() { return m_Data; }
        int GetWidth() { return m_Width; }
        int GetHeight() { return m_Height; }

        Texture2D *GenerateTexture();

        bool IsEnoughSpaceForCharacter(int glyphHeight);

        FreeTypeGlyph GetGlyphUVs(FT_GlyphSlot slot);

    private:
        int m_Width, m_Height;
        byte *m_Data;
        int m_XIndex, m_YIndex;
        int m_MaxHeight;
    };

    class FreeTypeFont {
    private:
        FT_Face m_Face;
        FreeTypeTexture *m_Texture;
        std::unordered_map<char, FreeTypeGlyph> m_Glyphs;

    public:
        FreeTypeFont(const char *path, float size);

        void LoadCharacter(char charcode);

        Texture2D *GenerateTexture();
    };
} }