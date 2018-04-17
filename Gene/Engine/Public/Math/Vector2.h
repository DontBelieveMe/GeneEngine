// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

namespace Gene {
	struct Vector2 
	{
		float X, Y;

		Vector2(float x, float y);
		Vector2();

		Vector2 operator+(const Vector2& b);
		Vector2 operator-(const Vector2& b);

        Vector2& operator+=(const Vector2& b);
        Vector2& operator-=(const Vector2& b);

        /** Return a new vector where the X & Y components are set to the X & Y of the left hand operand multiplied by the scalar value 'a'. */
        Vector2 operator*(const float& a);

        /** Set the X and Y components of this Vector to be the specified scalar value 'a'*/
        void Set(float a);
	};
}