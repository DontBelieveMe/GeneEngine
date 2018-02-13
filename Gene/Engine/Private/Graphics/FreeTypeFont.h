#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GeneCommon.h>
#include <Math/Vector2.h>
#include <Graphics/Texture2D.h>
#include <unordered_map>

namespace Gene { namespace Graphics {
    struct FreeTypeGlyph {
        Vector2 UV_TopLeft, 
                UV_TopRight,
                UV_BottomLeft, 
                UV_BottomRight;

        Vector2 Advance;
        
        int     Width, 
                Height;

        Vector2 Offset;
    };

    class FreeTypeTexture {
    public:
        FreeTypeTexture(int w, int h);
        ~FreeTypeTexture();

        void          CopyTextureToPos(int w, int h, byte *data, FT_GlyphSlot slot);
        int           GetWidth() { return m_Width; }
        int           GetHeight() { return m_Height; }

        Texture2D    *GenerateTexture();

        bool          IsEnoughSpaceForCharacter(int glyphHeight);

        FreeTypeGlyph GetGlyphUVs(FT_GlyphSlot slot);

    private:
        int           m_Width, 
                      m_Height;

        byte         *m_Data;
        
        int           m_XIndex, 
                      m_YIndex;
        
        int           m_MaxHeight;
    };

    class FreeTypeFont {
    private:
        FT_Face                                 m_Face;
        FreeTypeTexture                        *m_Texture;
        std::unordered_map<char, FreeTypeGlyph> m_Glyphs;

    public:
        FreeTypeFont(const char *path, float size);
        ~FreeTypeFont();

        void           LoadCharacter(char charcode);
        Texture2D     *GenerateTexture();
        FreeTypeGlyph *GetGlyph(char charcode);
        Vector2        GetKerning(char left, char right);
    };
} }