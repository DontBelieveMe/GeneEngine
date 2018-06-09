// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once
#include <Math/Vector3.h>
#include <Math/Vector2.h>

namespace gene {
	class Matrix4
	{
	public:
        static constexpr int ElementCount = 16; // 4 x 4 matrix
    
    public:
		float Elements[ElementCount];
	
    public:
		Matrix4(float diag=1.f);
		Matrix4(float elements[ElementCount]);
        
        // TODO: Convert this to the new immutable Matrix4 format
		void Invert();

        // TODO: Convert this to the new immutable Matrix4 format
		static Vector3 ScreenToWorld(
			Matrix4 projection, 
			Matrix4 view, 
			const Vector2& screenPos, 
            int viewWidth, int viewHeight
        );
        
        static Matrix4 RotateX(float theta);
        static Matrix4 RotateY(float theta);
        static Matrix4 RotateZ(float theta);

		static Matrix4 Translate(const Vector3& vector);
		static Matrix4 Translate(const Vector2& vector);

        static Matrix4 Scale(const Vector3& vector);
        static Matrix4 Scale(const Vector2& scale);
        static Matrix4 Scale(float scaleFactor);

		static Matrix4 Identity(float diag=1.f);
		static Matrix4 Perpective(float aspectRatio, float foV, float far, float near);
		static Matrix4 Orthographic(float right, float left, float top, float bottom, float far, float near);
		static Matrix4 LookAt(const Vector3& eyePosition, const Vector3& lookAtPos, const Vector3& upVector);

        Matrix4 Multiply(const Matrix4& other) const;
        Vector3 Multiply(const Vector3& other) const;
        
        Matrix4 operator*(const Matrix4& b);
        Vector3 operator*(const Vector3& b);
        Vector4 operator*(const Vector4& b);
	};
}
