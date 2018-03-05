#pragma once

#include <Graphics/Renderer2D.h>
#include <GeneUseAll.h>

#include <vector>

#include "cGameObject.h"

class cMap
{
private:
    std::vector<cGameObject*> m_gameObjects;

public:
    void Draw(Renderer2D *renderer);
    void Update(float dt);

    void AddGameObject(cGameObject *obj);
};