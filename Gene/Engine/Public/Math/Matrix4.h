#pragma once
#include <Math/Vector3.h>
#include <iostream>

namespace Gene { namespace Math {
	class Matrix4
	{
	public:
		static const int ElementCount = 16; // 4 x 4 matrix

	public:
		Matrix4(float diag=1.f);

		Matrix4 operator*(const Matrix4& other);
		
		float Elements[ElementCount];

		void Translate(const Vector3& vector);
		void Scale(const Vector3& vector);
		void RotateX(float theta);
		void RotateY(float theta);
		void RotateZ(float theta);

		static Matrix4 Identity(float diag=1.f);
		static Matrix4 Perpective(float aspectRatio, float foV, float far, float near);
		static Matrix4 Orthographic(float right, float left, float top, float bottom, float far, float near);

		friend std::ostream& operator<<(std::ostream& os, const Matrix4& matrix);
	};

	inline std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				os << matrix.Elements[j + i * 4] << ",";
			}
			os << std::endl;
		}
		return os;
	}
}}