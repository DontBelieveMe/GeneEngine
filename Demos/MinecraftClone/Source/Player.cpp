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
	
	int winWidth = window->Width();
    int winHeight = window->Height();
    
	static Vector2 lastMouse = input::Mouse::GetState().Position;
	Vector2 delta = window->WindowToScreen(input::Mouse::GetState().Position) - m_LastMousePos;
	static auto const BOUND = 89.9999;
	Rotation = Rotation + Vector3(delta.X*0.05f, delta.Y*0.05f, 0.f);
	if (Rotation.X >  BOUND) Rotation.X = BOUND;
	else if (Rotation.X < -BOUND) Rotation.X = -BOUND;

	if (Rotation.Y >  360) Rotation.Y = 0;
	else if (Rotation.Y <  0)   Rotation.Y = 360;

	//std::cout << delta.X << std::endl;
	input::Mouse::SetPosition({ winWidth / 2.f, winHeight / 2.f });
	lastMouse = window->WindowToScreen(input::Mouse::GetState().Position);
}

Matrix4 Player::GetViewMatrix()
{
    Vector3 negativeCamPos = Vector3::Negate(Position);
    Matrix4 translation;
    translation.Translate(negativeCamPos);
	translation.RotateY(Rotation.X);
	translation.RotateX(Rotation.Y);
	Matrix4 view;// = Matrix4::LookAt(Position, Position + m_Direction, m_Up);
    view = view.Multiply(translation);

	return view;
}
