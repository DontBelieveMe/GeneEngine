#pragma once

#include "cGameObject.h"

class cPlayer : public cGameObject
{
public:
    virtual void Draw(Renderer2D *renderer);
    virtual void Update(float dt);
};