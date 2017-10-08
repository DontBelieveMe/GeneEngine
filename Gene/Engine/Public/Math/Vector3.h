#pragma once

#include <Math/Vector2.h>

namespace Gene { namespace Math {
	struct Vector3 {
        float X, Y, Z;

		Vector3(float x, float y, float z);
		Vector3();
		Vector3(Vector2 vector, float z);

        Vector3        operator+(const Vector3& b);
        Vector3        operator-(const Vector3& b);

        static Vector3 Normalize(Vector3 vector);
        void           Normalize();

		static Vector3 Negate(Vector3 vector);

		static Vector3 CrossProduct(const Vector3& a, const Vector3& b);
        static float   DotProduct(const Vector3& a, const Vector3& b);

        float          Length();
	};
}}

namespace Gene {
	typedef Math::Vector3 Vector3;
}