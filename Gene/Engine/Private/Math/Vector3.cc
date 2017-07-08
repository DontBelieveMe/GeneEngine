#include <Math/Vector3.h>

#include <math.h>

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

Vector3 Vector3::operator-(const Vector3& b)
{
	X -= b.X;
	Y -= b.Y;
	Z -= b.Z;
	return *this;
}

Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)
{
	float cx = (a.Y * b.Z) - (a.Z * b.Y);
	float cy = (a.Z * b.X) - (a.X - b.Z);
	float cz = (a.X * b.Y) - (a.Y * b.X);
	return { cx, cy, cz };
}

Vector3 Vector3::Normalize(Vector3 vector)
{
	vector.Normalize();
	return vector;
}

void Vector3::Normalize()
{
	float len = Length();

	X /= len;
	Y /= len;
	Z /= len;
}

float Vector3::Length()
{
	return sqrtf((X * X) + (Y * Y) + (Z * Z));
}