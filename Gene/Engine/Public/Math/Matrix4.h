// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#pragma once
#include <Math/Vector3.h>
#include <Math/Vector2.h>

namespace Gene {
	class Matrix4
	{
	public:
        static constexpr int ElementCount = 16; // 4 x 4 matrix

	public:
		Matrix4(float diag=1.f);
		Matrix4(float elements[ElementCount]);

        Matrix4 Multiply(const Matrix4& other);
        Vector3 Multiply(const Vector3& other);

		float Elements[ElementCount];

		void Translate(const Vector3& vector);
		void Translate(const Vector2& vector);

		void Scale(const Vector3& vector);
		void Scale(const Vector2& vector);
		void Scale(float scaleFactor);

		void RotateX(float theta);
		void RotateY(float theta);
		void RotateZ(float theta);

		void Invert();

		Vector3 ScreenToWorld(
			Matrix4 projection, 
			Matrix4 view, 
			const Vector2& screenPos, 
            int viewWidth, int viewHeight
        );

		static Matrix4 Identity(float diag=1.f);
		static Matrix4 Perpective(float aspectRatio, float foV, float far, float near);
		static Matrix4 Orthographic(float right, float left, float top, float bottom, float far, float near);
		static Matrix4 LookAt(const Vector3& eyePosition, const Vector3& lookAtPos, const Vector3& upVector);

        friend Matrix4 operator*(Matrix4 a, const Matrix4& b);
        friend Vector3 operator*(Matrix4 a, const Vector3& b);
	};
}
