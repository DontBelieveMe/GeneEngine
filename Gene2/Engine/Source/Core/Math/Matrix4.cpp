// Copyright 2017-2019 Barney Wilks. All Rights Reserved

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

Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& centre, const Vector3& up)
{
	Vector3 f { centre.X - eye.X, centre.Y - eye.Y, centre.Z - eye.Z };
	f.Normalize();

	Vector3 s = Vector3::CrossProduct(f, up);
	s.Normalize();

	Vector3 u = Vector3::CrossProduct(s, f);

	Matrix4 mat4 = Matrix4::FromElements(
		s.X, u.X, -f.X, 0.f,
		s.Y, u.Y, -f.Y, 0.f,
		s.Z, u.Z, -f.Z, 0.f,
		-Vector3::DotProduct(s, eye), -Vector3::DotProduct(u, eye), -Vector3::DotProduct(f, eye), 1.f
	);

	return mat4;
}

Matrix4 Matrix4::FromElements(
	float m00, float m10, float m20, float m30,
	float m01, float m11, float m21, float m31,
	float m02, float m12, float m22, float m32,
	float m03, float m13, float m23, float m33
)
{
	Matrix4 mat4;

	mat4.Elements[0 + 0 * 4] = m00;
	mat4.Elements[1 + 0 * 4] = m10;
	mat4.Elements[2 + 0 * 4] = m20;
	mat4.Elements[3 + 0 * 4] = m30;

	mat4.Elements[0 + 1 * 4] = m01;
	mat4.Elements[1 + 1 * 4] = m11;
	mat4.Elements[2 + 1 * 4] = m21;
	mat4.Elements[3 + 1 * 4] = m31;

	mat4.Elements[0 + 2 * 4] = m02;
	mat4.Elements[1 + 2 * 4] = m12;
	mat4.Elements[2 + 2 * 4] = m22;
	mat4.Elements[3 + 2 * 4] = m32;

	mat4.Elements[0 + 3 * 4] = m03;
	mat4.Elements[1 + 3 * 4] = m13;
	mat4.Elements[2 + 3 * 4] = m23;
	mat4.Elements[3 + 3 * 4] = m33;

	return mat4;
}

Matrix4 Matrix4::MakePerspective(const float& aspectRatio, const float& fov, const float& far, const float& near)
{
	Matrix4 m4;
	m4.SetIdentity();

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
