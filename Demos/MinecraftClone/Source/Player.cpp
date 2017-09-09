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

	input::MouseState mouse = input::Mouse::GetState();

    int winWidth = window->Width();
    int winHeight = window->Height();
    float deltaTime = 1.6f;

    m_HorizontalAngle += 0.005f * deltaTime * float(winWidth / 2 - mouse.Position.X);
    m_VerticalAngle += 0.005f * deltaTime * float(winHeight / 2 - mouse.Position.Y);
    //printf("%f %f\n", m_HorizontalAngle, m_VerticalAngle);
    m_HorizontalAngle = 0;
    m_VerticalAngle = 0;
    Vector3 direction(
        cos(m_VerticalAngle) * sin(m_HorizontalAngle),
        sin(m_VerticalAngle),
        cos(m_VerticalAngle) * cos(m_HorizontalAngle)
    );

    Vector3 right(
        sin(m_HorizontalAngle - 3.14f/2.0f),
        0,
        cos(m_HorizontalAngle - 3.14f/2.0f)
    );

    m_Up = Vector3::CrossProduct(right, direction);
    m_Direction = direction;
}

Matrix4 Player::GetViewMatrix()
{
    Vector3 negativeCamPos = Vector3::Negate(Position);
    Matrix4 translation;
    translation.Translate(negativeCamPos);

    Matrix4 view = Matrix4::LookAt(Position, Position+m_Direction, m_Up);
    view = view.Multiply(translation);

	return view;
}
