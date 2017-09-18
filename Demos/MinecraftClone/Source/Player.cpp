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
	int winWidth = window->Width();
    int winHeight = window->Height();
	
	float speed = 3.0f;
	float mouseSpeed = 3.5f;

	Vector2 mousePos = input::Mouse::GetState().Position;
	input::Mouse::SetPosition({winWidth/2.f, winHeight/2.f});

	m_HorizontalAngle += mouseSpeed * float(time.DeltaInMilliSeconds()*0.001) * float(winWidth / 2 - mousePos.X);
	m_VerticalAngle   += mouseSpeed * float(time.DeltaInMilliSeconds()*0.001) * float(winHeight / 2 - mousePos.Y);
	printf("%f %f\n", m_HorizontalAngle);
	//printf("%f\n", time.DeltaInMilliSeconds());
	m_VerticalAngle = 1.f;
	m_Direction = Vector3(
		cos(m_VerticalAngle) * sin(m_HorizontalAngle),
		sin(m_VerticalAngle),
		cos(m_VerticalAngle) * cos(m_HorizontalAngle)
	);

	Vector3 right(
		sin(m_HorizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_HorizontalAngle - 3.14f / 2.0f)
	);

	m_Up = Vector3::CrossProduct(right, m_Direction);
}

Matrix4 Player::GetViewMatrix()
{
	Matrix4 view = Matrix4::LookAt(Position, Position + m_Direction, m_Up);
	return view;
}
