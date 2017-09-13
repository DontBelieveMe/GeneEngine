#include <Math/Vector2.h>

using namespace Gene::Math;

Vector2::Vector2() :
	X(0.0f), Y(0.0f)
{
}

Vector2::Vector2(float x, float y) :
	X(x), Y(y)
{
}

Vector2 Vector2::operator+(const Vector2& b)
{
	X += b.X;
	Y += b.Y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& b)
{
	X -= b.X;
	Y -= b.Y;
	return *this;
}