#pragma once

namespace Gene {
	namespace Math {
		struct Vector2 
		{
			float X, Y;

			Vector2(float x, float y);
			Vector2();

			Vector2 operator+(const Vector2& b);
			Vector2 operator-(const Vector2& b);
		};
	}

	typedef Math::Vector2 Vector2;
}