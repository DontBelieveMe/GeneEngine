// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Runtime/Reflection.h>

namespace gene {
	struct Vector2 
	{
		float X, Y;

		Vector2(float x, float y);
		Vector2();

		Vector2 operator+(const Vector2& b);
		Vector2 operator-(const Vector2& b) const;

        Vector2& operator+=(const Vector2& b);
        Vector2& operator+=(const float& other);
        Vector2& operator-=(const Vector2& b);

        /** Return a new vector where the X & Y components are set to the X & Y of the left hand operand multiplied by the scalar value 'a'. */
        Vector2 operator*(const float& a);

        /** Set the X and Y components of this Vector to be the specified scalar value 'a'*/
        void Set(float a);

        /** Normalizes this vector in place.*/
        void Normalize();

        float Length();

        META_CLASS_REFLECTED(gene::Vector2)
	};
    void dud();

    template <typename T>
    struct TVector2 {
        T X, Y;

        TVector2(const T& x, const T& y) : X(x), Y(y) {}
        TVector2(const T& a) : X(a), Y(a) {}
        TVector2() {}
        void Set(const T& a)
        {
            X = a;
            Y = a;
        }
    };

    typedef TVector2<float> Vector2f;
    typedef TVector2<int> Vector2i;
}