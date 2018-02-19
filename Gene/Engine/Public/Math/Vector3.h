#pragma once

#include <Math/Vector2.h>

namespace Gene { namespace Math {
    /** Class that represents a 3 component floating point vector (XYZ). */
	struct Vector3 {
        float X, Y, Z;

        /** Initalizes the X, Y and Z member variables to those specified in constructor. */
		Vector3(float x, float y, float z);

        /** Sets X, Y and Z componts all to zero. */
		Vector3();

        /** Sets the X and Y components to that of the Vector2 specified and sets Z to the one specified.*/
		Vector3(Vector2 vector, float z);

        Vector3        operator+(const Vector3& b);
        Vector3        operator-(const Vector3& b);

        /** Returns a vector that is the normalized version of the one specfied. Original vector is not touched. */
        static Vector3 Normalize(Vector3 vector);

        /** Normalizes this vector in place.*/
        void           Normalize();

        /** Returns the opposite vector of the one specified (e.g all components negated). Original vector not modified. */
		static Vector3 Negate(Vector3 vector);

        /** Returns the cross product of the two vectors a & b. */
		static Vector3 CrossProduct(const Vector3& a, const Vector3& b);

        /** Returns the dot product of the two vectors a & b. */
        static float   DotProduct(const Vector3& a, const Vector3& b);

        /** Returns the length (magnitude) of this vector. Involves a square root operation. */
        float          Length();
	};
}}

namespace Gene {
	typedef Math::Vector3 Vector3;
}
