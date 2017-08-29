#pragma once

#include <Graphics/Renderable2D.h>
#include <Graphics/Texture2D.h>

#include <vector>

namespace Gene { namespace Graphics {
    class Spritesheet {
    private:
        std::vector<Renderable2D*> m_CachedSprites;
        Texture2D* m_SpritesheetTexture;
        int m_SpriteWidth, m_SpriteHeight;

    public:
        Spritesheet(const char *filepath, float spriteWidth, float spriteHeight);
        ~Spritesheet();

        Renderable2D *GetSprite(int x, int y);
    };
}}
