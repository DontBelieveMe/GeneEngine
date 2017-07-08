#pragma once

namespace Gene {
	namespace Math {
		template <typename T>
		struct Vector2T 
		{
			T X, Y;
			Vector2T(T x, T y) : X(x), Y(y) {}
		};

		typedef Vector2T<int> Vector2i;

		struct Vector2 
		{
			float X, Y;

			Vector2(float x, float y);
			Vector2();

			Vector2 operator+(const Vector2& b);
		};
	}
}