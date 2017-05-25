#include <Math/Matrix4.h>
#include <Math/Functions.h>

#include <string.h>
#include <math.h>

using namespace Gene::Math;

Matrix4::Matrix4(float diag)
{
	for (int i = 0; i < Matrix4::ElementCount; ++i)
	{
		Elements[i] = 0.f;
	}

	Elements[0]		   = diag;
	Elements[1 + 1 * 4]  = diag;
	Elements[2 + 2 * 4]  = diag;
	Elements[3 + 3 * 4]  = diag;
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
	float data[Matrix4::ElementCount];
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++)
			{
				sum += Elements[e + row * 4] * other.Elements[col + e * 4];
			}
			data[col + row * 4] = sum;
		}
	}
	memcpy(Elements, data, Matrix4::ElementCount * sizeof(float));
	return *this;
}

void Matrix4::Translate(const Vector3& vector)
{
	Elements[3 + 0 * 4] = vector.X;
	Elements[3 + 1 * 4] = vector.Y;
	Elements[3 + 2 * 4] = vector.Z;
}

void Matrix4::Translate(const Vector2& vector)
{
	Elements[3 + 0 * 4] = vector.X;
	Elements[3 + 1 * 4] = vector.Y;
}

void Matrix4::Scale(const Vector3& vector)
{
	Elements[0] = vector.X;
	Elements[1 + 1 * 4] = vector.Y;
	Elements[2 + 2 * 4] = vector.Z;
}

void Matrix4::Scale(const Vector2& vector)
{
	Elements[0] = vector.X;
	Elements[1 + 1 * 4] = vector.Y;
}

void Matrix4::Scale(float scaleFactor)
{
	Elements[0] = scaleFactor;
	Elements[1 + 1 * 4] = scaleFactor;
	Elements[2 + 2 * 4] = scaleFactor;
}

void Matrix4::RotateX(float theta)
{
	float radians = Maths::ToRadians(theta);
	Elements[1 + 1 * 4] = ::cos(radians);
	Elements[2 + 2 * 4] = ::cos(radians);
	Elements[1 + 2 * 4] = ::sin(radians);
	Elements[2 + 1 * 4] = -(::sin(radians));
}

void Matrix4::RotateY(float theta)
{
	float radians = Maths::ToRadians(theta);
	Elements[0] = ::cos(radians);
	Elements[2 + 2 * 4] = ::cos(radians);
	Elements[0 + 2 * 4] = -(::sin(radians));
	Elements[2 + 0 * 4] = ::sin(radians);
}

void Matrix4::RotateZ(float theta)
{
	float radians = Maths::ToRadians(theta);
	Elements[0] = ::cos(radians);
	Elements[1 + 1 * 4] = ::cos(radians);
	Elements[0 + 1 * 4] = ::sin(radians);
	Elements[1 + 0 * 4] = -(::sin(radians));
}

Matrix4 Matrix4::Identity(float diag)
{
	return Matrix4(diag);
}

Matrix4 Matrix4::Perpective(float aspectRatio, float foV, float near, float far)
{
	Matrix4 matrix = Matrix4::Identity();
	matrix.Elements[0] = (1.0f / ::tan(Maths::ToRadians(0.5f * foV))) / aspectRatio;
	matrix.Elements[1 + 1 * 4] = 1.0f / ::tan(Maths::ToRadians(0.5f * foV));
	matrix.Elements[2 + 2 * 4] = (near + far) / (near - far);
	matrix.Elements[2 + 3 * 4] = -1.f;
	matrix.Elements[3 + 2 * 4] = (2.f * near * far) / (near - far);

	return matrix;
}

Matrix4 Matrix4::Orthographic(float right, float left, float bottom, float top, float far, float near)
{
	Matrix4 matrix = Matrix4::Identity();
	matrix.Elements[0] = 0.5f * (right - left);
	matrix.Elements[1 + 1 * 4] = 0.5f * (top - bottom);
	matrix.Elements[2 + 2 * 4] = -2 / (far - near);
	matrix.Elements[3 + 3 * 4] = 1.0f;
	matrix.Elements[3 + 0 * 4] = -((right + left) / (right - left));
	matrix.Elements[3 + 0 * 4] = -((top + bottom) / (top - bottom));
	matrix.Elements[3 + 0 * 4] = -((far + near) / (far - near));
	return matrix;
}


