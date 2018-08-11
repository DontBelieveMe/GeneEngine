// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Math/Vector2.h>
#include <Math/Functions.h>

using namespace gene;

Vector2::Vector2() :
	X(0.0f), Y(0.0f)
{
}

Vector2::Vector2(float x, float y) :
	X(x), Y(y)
{
}

float Vector2::Length()
{
    return Maths::Sqrt((X * X) + (Y * Y));
}

void Vector2::Normalize() 
{
    float len = Length();

    X /= len;
    Y /= len;
}

Vector2 Vector2::operator+(const Vector2& b)
{
	Vector2 result;
    result.X = X + b.X;
	result.Y = Y + b.Y;
	return result;
}

Vector2 Vector2::operator-(const Vector2& b) const
{
	return Vector2(X - b.X, Y - b.Y);
}

Vector2 Vector2::operator*(const float& a)
{
    return Vector2(X * a, Y * a);
}

Vector2& Vector2::operator+=(const float& other)
{
    this->X += other;
    this->Y += other;

    return *this;
}

Vector2& Vector2::operator+=(const Vector2& b)
{
    this->X += b.X;
    this->Y += b.Y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& b)
{
    this->X -= b.X;
    this->Y -= b.Y;

    return *this;
}

void Vector2::Set(float a)
{
    X = a;
    Y = a;
}