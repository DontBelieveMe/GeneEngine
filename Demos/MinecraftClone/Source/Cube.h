#pragma once

#include "GameObject.h"

class CubeTexturePreset {
	Vector2 Top;
};

class Cube : public GameObject {
public:
	Cube(Vector3 pos, GeneModel *mesh);
};