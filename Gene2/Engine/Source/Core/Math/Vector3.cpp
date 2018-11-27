// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Gene2/Core/Math/Vector3.hpp>
#include <Gene2/Core/StdLib/Math.hpp>

using namespace g2;

Vector3::Vector3()
	: X(0.f), Y(0.f), Z(0.f) {}

Vector3::Vector3(const float& x, const float& y, const float& z)
	: X(x), Y(y), Z(z) {}

Vector3::Vector3(const float& a)
	: X(a), Y(a), Z(a) {}

void Vector3::Normalize()
{
	const float s = (X*X) + (Y*Y) + (Z*Z);
	const float s2 = Math::InvSqrt(s);

	X *= s2;
	Y *= s2;
	Z *= s2;
}

float Vector3::Length() const
{
	return Math::Sqrt((X * X) + (Y * Y) + (Z * Z));
}