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

Matrix4 Matrix4::operator*(const Vector2& vector)
{
	return Matrix4::Identity();
}

Vector3 Matrix4::ScreenToWorld(Matrix4 projection, Matrix4 view, const Vector2& screenPos, int viewWidth, int viewHeight)
{
	Vector3 pos;
	pos.X = 2.f * screenPos.X / static_cast<float>(viewWidth - 1);
	pos.Y = -(2.f * screenPos.Y / static_cast<float>(viewHeight - 1));
	pos.Z = 0;
	
	view.Invert();
	projection.Invert();
	view.Translate(pos);
	projection.Translate(pos);
	return pos;
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
	matrix.Elements[3 + 1 * 4] = -((top + bottom) / (top - bottom));
	matrix.Elements[3 + 2 * 4] = -((far + near) / (far - near));
	return matrix;
}

Matrix4 Matrix4::LookAt(const Vector3 & eyePosition, const Vector3 & lookAtPos, const Vector3 & upVector)
{
	Matrix4 result;
	Vector3 x, y, z;
	z = Vector3(
		eyePosition.X - lookAtPos.X,
		eyePosition.Y - lookAtPos.Y,
		eyePosition.Z - lookAtPos.Z
	);
	z.Normalize();
	y = upVector;
	x = Vector3::CrossProduct(y, z);
	y = Vector3::CrossProduct(z, x);
	x.Normalize();
	y.Normalize();
	
	result.Elements[0]         = x.X;
	result.Elements[1 + 0 * 4] = x.Y;
	result.Elements[2 + 0 * 4] = x.Z;
	result.Elements[3 + 0 * 4] = -Vector3::DotProduct(x, eyePosition);

	result.Elements[0 + 1 * 4] = y.X;
	result.Elements[1 + 1 * 4] = y.Y;
	result.Elements[2 + 1 * 4] = y.Z;
	result.Elements[3 + 1 * 4] = -Vector3::DotProduct(y, eyePosition);

	result.Elements[0 + 2 * 4] = z.X;
	result.Elements[1 + 2 * 4] = z.Y;
	result.Elements[2 + 2 * 4] = z.Z;
	result.Elements[3 + 2 * 4] = -Vector3::DotProduct(z, eyePosition);

	result.Elements[0 + 3 * 4] = 0.f;
	result.Elements[1 + 3 * 4] = 0.f;
	result.Elements[2 + 3 * 4] = 0.f;
	result.Elements[3 + 3 * 4] = 1.f;
	return result;
}

/*
	Copied from Sparky maths - mat4.cpp
*/
void Matrix4::Invert()
{
	float temp[16];

		temp[0] = Elements[5] * Elements[10] * Elements[15] -
			Elements[5] * Elements[11] * Elements[14] -
			Elements[9] * Elements[6] * Elements[15] +
			Elements[9] * Elements[7] * Elements[14] +
			Elements[13] * Elements[6] * Elements[11] -
			Elements[13] * Elements[7] * Elements[10];

		temp[4] = -Elements[4] * Elements[10] * Elements[15] +
			Elements[4] * Elements[11] * Elements[14] +
			Elements[8] * Elements[6] * Elements[15] -
			Elements[8] * Elements[7] * Elements[14] -
			Elements[12] * Elements[6] * Elements[11] +
			Elements[12] * Elements[7] * Elements[10];

		temp[8] = Elements[4] * Elements[9] * Elements[15] -
			Elements[4] * Elements[11] * Elements[13] -
			Elements[8] * Elements[5] * Elements[15] +
			Elements[8] * Elements[7] * Elements[13] +
			Elements[12] * Elements[5] * Elements[11] -
			Elements[12] * Elements[7] * Elements[9];

		temp[12] = -Elements[4] * Elements[9] * Elements[14] +
			Elements[4] * Elements[10] * Elements[13] +
			Elements[8] * Elements[5] * Elements[14] -
			Elements[8] * Elements[6] * Elements[13] -
			Elements[12] * Elements[5] * Elements[10] +
			Elements[12] * Elements[6] * Elements[9];

		temp[1] = -Elements[1] * Elements[10] * Elements[15] +
			Elements[1] * Elements[11] * Elements[14] +
			Elements[9] * Elements[2] * Elements[15] -
			Elements[9] * Elements[3] * Elements[14] -
			Elements[13] * Elements[2] * Elements[11] +
			Elements[13] * Elements[3] * Elements[10];

		temp[5] = Elements[0] * Elements[10] * Elements[15] -
			Elements[0] * Elements[11] * Elements[14] -
			Elements[8] * Elements[2] * Elements[15] +
			Elements[8] * Elements[3] * Elements[14] +
			Elements[12] * Elements[2] * Elements[11] -
			Elements[12] * Elements[3] * Elements[10];

		temp[9] = -Elements[0] * Elements[9] * Elements[15] +
			Elements[0] * Elements[11] * Elements[13] +
			Elements[8] * Elements[1] * Elements[15] -
			Elements[8] * Elements[3] * Elements[13] -
			Elements[12] * Elements[1] * Elements[11] +
			Elements[12] * Elements[3] * Elements[9];

		temp[13] = Elements[0] * Elements[9] * Elements[14] -
			Elements[0] * Elements[10] * Elements[13] -
			Elements[8] * Elements[1] * Elements[14] +
			Elements[8] * Elements[2] * Elements[13] +
			Elements[12] * Elements[1] * Elements[10] -
			Elements[12] * Elements[2] * Elements[9];

		temp[2] = Elements[1] * Elements[6] * Elements[15] -
			Elements[1] * Elements[7] * Elements[14] -
			Elements[5] * Elements[2] * Elements[15] +
			Elements[5] * Elements[3] * Elements[14] +
			Elements[13] * Elements[2] * Elements[7] -
			Elements[13] * Elements[3] * Elements[6];

		temp[6] = -Elements[0] * Elements[6] * Elements[15] +
			Elements[0] * Elements[7] * Elements[14] +
			Elements[4] * Elements[2] * Elements[15] -
			Elements[4] * Elements[3] * Elements[14] -
			Elements[12] * Elements[2] * Elements[7] +
			Elements[12] * Elements[3] * Elements[6];

		temp[10] = Elements[0] * Elements[5] * Elements[15] -
			Elements[0] * Elements[7] * Elements[13] -
			Elements[4] * Elements[1] * Elements[15] +
			Elements[4] * Elements[3] * Elements[13] +
			Elements[12] * Elements[1] * Elements[7] -
			Elements[12] * Elements[3] * Elements[5];

		temp[14] = -Elements[0] * Elements[5] * Elements[14] +
			Elements[0] * Elements[6] * Elements[13] +
			Elements[4] * Elements[1] * Elements[14] -
			Elements[4] * Elements[2] * Elements[13] -
			Elements[12] * Elements[1] * Elements[6] +
			Elements[12] * Elements[2] * Elements[5];

		temp[3] = -Elements[1] * Elements[6] * Elements[11] +
			Elements[1] * Elements[7] * Elements[10] +
			Elements[5] * Elements[2] * Elements[11] -
			Elements[5] * Elements[3] * Elements[10] -
			Elements[9] * Elements[2] * Elements[7] +
			Elements[9] * Elements[3] * Elements[6];

		temp[7] = Elements[0] * Elements[6] * Elements[11] -
			Elements[0] * Elements[7] * Elements[10] -
			Elements[4] * Elements[2] * Elements[11] +
			Elements[4] * Elements[3] * Elements[10] +
			Elements[8] * Elements[2] * Elements[7] -
			Elements[8] * Elements[3] * Elements[6];

		temp[11] = -Elements[0] * Elements[5] * Elements[11] +
			Elements[0] * Elements[7] * Elements[9] +
			Elements[4] * Elements[1] * Elements[11] -
			Elements[4] * Elements[3] * Elements[9] -
			Elements[8] * Elements[1] * Elements[7] +
			Elements[8] * Elements[3] * Elements[5];

		temp[15] = Elements[0] * Elements[5] * Elements[10] -
			Elements[0] * Elements[6] * Elements[9] -
			Elements[4] * Elements[1] * Elements[10] +
			Elements[4] * Elements[2] * Elements[9] +
			Elements[8] * Elements[1] * Elements[6] -
			Elements[8] * Elements[2] * Elements[5];

		float determinant = Elements[0] * temp[0] + Elements[1] * temp[4] + Elements[2] * temp[8] + Elements[3] * temp[12];
		determinant = 1.0f / determinant;

		for (unsigned i = 0; i < 4 * 4; i++)
			Elements[i] = temp[i] * determinant;
}
