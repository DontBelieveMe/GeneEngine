#pragma once

namespace Gene { namespace Math {
	class Matrix4
	{
	public:
		static const int ElementCount = 16; // 4 x 4 matrix

	public:
		Matrix4(float diag=0.f);

		Matrix4 operator*(const Matrix4& other);
		
		float Elements[ElementCount];
	};
}}