#pragma once

#include <vector>

#include <Content/GeneModel.h>
#include "GameObject.h"
#include <Graphics/VertexArray.h>
#include "Shaders.h"
#include <GeneUseAll.h>

class Renderer 
{
private:
	std::vector<GameObject*> m_Objects;
	Shaders& m_Shaders;

public:
	Renderer(Shaders& shaders) : m_Shaders(shaders) {}

	void SubmitMesh(GameObject *mesh);

	void Draw();
};