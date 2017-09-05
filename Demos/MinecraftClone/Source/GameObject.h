#pragma once

#include <Math/Vector3.h>
#include <Content/GeneModel.h>
#include <GeneUseAll.h>
#include "RenderItem.h"
class GameObject {
public:
	GeneModel	*Mesh;
	Vector3		 Position;
	RenderItem	 DrawInfo;
	Vector3		 Rotation;

	GameObject(const Vector3& pos, GeneModel *model) : Mesh(model), Position(pos) {}

	inline bool HasRenderableModel() const { return Mesh != NULL; }
};