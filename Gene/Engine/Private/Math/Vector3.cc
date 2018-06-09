// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Math/Vector3.h>

#include <math.h>

using namespace gene;

Vector3::Vector3():
	X(0.0f), Y(0.0f), Z(0.0f)
{
}

Vector3::Vector3(float x, float y, float z):
	X(x), Y(y), Z(z)
{
}

Vector3::Vector3(Vector2 vector, float z) :
	X(vector.X), Y(vector.Y), Z(z) 
{
}

Vector3 Vector3::operator+(const Vector3& b)
{
	return Vector3(X + b.X, Y + b.Y, Z + b.Z);
}

Vector3 Vector3::operator-(const Vector3& b)
{
	return Vector3(X - b.X, Y - b.Y, Z - b.Z);
}

Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)
{
	float cx = (a.Y * b.Z) - (a.Z * b.Y);
	float cy = (a.Z * b.X) - (a.X * b.Z);
	float cz = (a.X * b.Y) - (a.Y * b.X);
	return { cx, cy, cz };
}

Vector3 Vector3::Normalize(Vector3 vector)
{
	vector.Normalize();
	return vector;
}

Vector3 Vector3::Negate(Vector3 vector)
{
	vector.X = -vector.X;
	vector.Y = -vector.Y;
	vector.Z = -vector.Z;
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

float Vector3::DotProduct(const Vector3& a, const Vector3& b)
{
	float dot = a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	return dot;
}