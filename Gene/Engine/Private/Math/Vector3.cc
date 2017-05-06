#include <Math/Vector3.h>

using namespace Gene::Math;

Vector3::Vector3():
	X(0.0f), Y(0.0f), Z(0.0f)
{
}

Vector3::Vector3(float x, float y, float z):
	X(x), Y(y), Z(z)
{
}

Vector3 Vector3::operator+(const Vector3& b)
{
	X += b.X;
	Y += b.Y;
	Z += b.Z;
	return *this;
}