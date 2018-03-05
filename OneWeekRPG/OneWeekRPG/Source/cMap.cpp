#include "cMap.h"

#include <algorithm>  

void cMap::Draw(Renderer2D *renderer)
{
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(), [&](cGameObject* obj) {
        obj->Draw(renderer);
    });
}

void cMap::Update(float dt)
{
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(), [&](cGameObject* obj) {
        obj->Update(dt);
    });
}

void cMap::AddGameObject(cGameObject *obj)
{
    m_gameObjects.push_back(obj);
}