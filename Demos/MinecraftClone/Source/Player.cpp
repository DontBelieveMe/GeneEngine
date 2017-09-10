#include "Player.h"

#include <Math/Functions.h>
#include <Input/Keyboard.h>
#include <Input/Keys.h>
#include <Input/Mouse.h>
#include <math.h>

Player::Player(const Vector3& pos) : GameObject(pos, NULL)
{
    m_HorizontalAngle = 0.f;
    m_VerticalAngle = 0.f;
}

void Player::Tick(Window* window, const GameTime& time)
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
	else if (state.IsKeyDown(input::Keys::A)) {
		m_Direction.Y -= speed/2;
	} else if (state.IsKeyDown(input::Keys::D)) {
		m_Direction.Y += speed/2;
	}

	input::MouseState mouse = input::Mouse::GetState();

    int winWidth = window->Width();
    int winHeight = window->Height();
    float deltaTime = 1.6f;
}

Matrix4 Player::GetViewMatrix()
{
    Vector3 negativeCamPos = Vector3::Negate(Position);
    Matrix4 translation;
    translation.Translate(negativeCamPos);
	translation.RotateY(m_Direction.Y);
	Matrix4 view;// = Matrix4::LookAt(Position, Position + m_Direction, m_Up);
    view = view.Multiply(translation);

	return view;
}
