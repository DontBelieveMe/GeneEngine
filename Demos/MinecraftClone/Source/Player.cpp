#include "Player.h"

#include <Math/Functions.h>
#include <Input/Keyboard.h>
#include <Input/Mouse.h>

Player::Player(const Vector3& pos) : GameObject(pos, NULL)
{
}

void Player::Tick(float delta)
{
	namespace input = Gene::Input;

	input::KeyboardState state = input::Keyboard::GetState();

	const float speed = 0.4f;
	if (state.IsKeyDown(input::Keys::W))
	{
		Position.Z -= speed;
	}
	else if (state.IsKeyDown(input::Keys::S))
	{
		Position.Z += speed;
	}

	input::MouseState mouse = input::Mouse::GetState();
	Vector2 mousePos = mouse.Position;
	Vector2 deltaMousePos(mousePos.X - m_LastMousePos.X, mousePos.Y - m_LastMousePos.Y);
	printf("X: %f, Y: %f\n", deltaMousePos.X, deltaMousePos.Y);
    //Rotation.Y += sin(deltaMousePos.X);
    //Rotation.X += cos(deltaMousePos.Y);
	m_LastMousePos = mousePos;
}

Matrix4 Player::GetViewMatrix()
{
	Matrix4 view;
	view.RotateX(Rotation.X);
	view.RotateY(Rotation.Y);
	Vector3 negativeCamPos = Vector3::Negate(Position);
	
	view.Translate(negativeCamPos);
	return view;
}
