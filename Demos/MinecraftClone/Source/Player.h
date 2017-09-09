#pragma once

#include <Math/Vector3.h>
#include <Math/Matrix4.h>
#include <Math/Vector2.h>
#include <Platform/Time.h>
#include <Platform/Window.h>

#include <GeneUseAll.h>

#include "GameObject.h"

class Player : public GameObject
{
private:
	Vector2 m_LastMousePos;
    Vector3 m_Direction;
    Vector3 m_Up;
    float m_HorizontalAngle = 0.f,
          m_VerticalAngle = 0.f;

public:
	Player(const Vector3& position);
    void Tick(Window* window, const GameTime& time);

	Matrix4 GetViewMatrix();
};
