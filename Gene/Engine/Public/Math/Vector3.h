#pragma once

namespace Gene { namespace Math {
	struct Vector3 {
		float X, Y, Z;

		Vector3(float x, float y, float z);
		Vector3();

		Vector3 operator+(const Vector3& b);
		Vector3 operator-(const Vector3& b);

		static Vector3 Normalize(Vector3 vector);
		void Normalize();

		static Vector3 CrossProduct(const Vector3& a, const Vector3& b);

		float Length();
	};
}}