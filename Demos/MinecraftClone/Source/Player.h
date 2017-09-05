#pragma once

#include <Math/Vector3.h>
#include <Math/Matrix4.h>
#include <Math/Vector2.h>
#include <GeneUseAll.h>

#include "GameObject.h"

class Player : public GameObject
{
private:
	Vector2 m_LastMousePos;

public:
	Player(const Vector3& position);
	void Tick(float delta);

	Matrix4 GetViewMatrix();
};