// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Gene2/Core/Math/Matrix4.hpp>
#include <Gene2/Core/StdLib/Math.hpp>

using namespace g2;

#define M(ptr, x, y) ptr[x + y * 4]

void Matrix4::SetIdentity()
{
	for (int i = 0; i < 16; ++i) 
	{
		Elements[i] = 0.f;
	}

	M(Elements, 0, 0) = 1.f;
	M(Elements, 1, 1) = 1.f;
	M(Elements, 2, 2) = 1.f;
	M(Elements, 3, 3) = 1.f;
}

Matrix4 Matrix4::MakePerspective(const float& aspectRatio, const float& fov, const float& far, const float& near)
{
	Matrix4 m4;
	m4.SetIdentity();

	const float t = (-2.f * far * near) / (far - near);
	const float thf = Math::Tan(Math::DegreesToRadians(fov * 0.5f));

	M(m4.Elements, 0, 0) = 1.f / (aspectRatio * thf);
	M(m4.Elements, 1, 1) = 1.f / thf;
	M(m4.Elements, 2, 2) = -(far + near) / (far - near);
	M(m4.Elements, 3, 2) = -1.f;
	M(m4.Elements, 2, 3) = -(2.f * far * near) / (far - near);
	M(m4.Elements, 3, 3) = 0.f;

	return m4;
}

Matrix4 Matrix4::MakeOrthographic(const float& left, const float& right, const float& top, const float& bottom, const float& far, const float& near)
{
	Matrix4 m4;
	m4.SetIdentity();

	M(m4.Elements, 0, 0) = 2.f / (right - left);
	M(m4.Elements, 1, 1) = 2.f / (top - bottom);
	M(m4.Elements, 2, 2) = -2.f / (far - near);
	M(m4.Elements, 3, 3) = 1.f;
	M(m4.Elements, 3, 0) = (left + right) / (left - right);
	M(m4.Elements, 3, 1) = (bottom + top) / (bottom - top);
	M(m4.Elements, 3, 2) = (far + near) / (far - near);

	return m4;
}

Matrix4 g2::operator*(const Matrix4& left, const Matrix4& right)
{
	Matrix4 m4;
	
	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			float xy = 0.f;
			for (int k = 0; k < 4; ++k)
			{
				xy += M(left.Elements, x, k) * M(right.Elements, k, y);
			}

			M(m4.Elements, x, y) = xy;
		}
	}

	return m4;
}