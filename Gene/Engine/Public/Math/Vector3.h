#pragma once

namespace Gene { namespace Math {
	struct Vector3 {
		float X, Y, Z;

		Vector3(float x, float y, float z);
		Vector3();

		Vector3 operator+(const Vector3& b);
	};
}}