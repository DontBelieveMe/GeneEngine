#pragma once

#include <Graphics/Renderer2D.h>
#include <Math/Vector2.h>
#include <GeneUseAll.h>

class cGameObject {
public:
    virtual void Draw(Renderer2D *renderer) = 0;
    virtual void Update(float dt) = 0;

    Vector2 Position;
};