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

void Matrix4::Scale(const Vector3& vector)
{
	Elements[0] = vector.X;
	Elements[1 + 1 * 4] = vector.Y;
	Elements[2 + 2 * 4] = vector.Z;

}

Matrix4 Matrix4::Identity(float diag)
{
	return Matrix4(diag);
}

Matrix4 Matrix4::Perpective(float aspectRatio, float foV, float near, float far)
{
	Matrix4 matrix = Matrix4::Identity();
	/*matrix.Elements[0] = 1 / (aspectRatio * ::tan(Maths::ToRadians(foV / 2)));
	matrix.Elements[1 + 1 * 4] = 1 / (::tan(Maths::ToRadians(foV / 2)));
	matrix.Elements[2 + 2 * 4] = -((far + near) / (far - near));
	matrix.Elements[2 + 3 * 4] = -1.f;
	matrix.Elements[3 + 2 * 4] = -((2 * far * near) / (far - near));*/
	matrix.Elements[0] = (1.0f / ::tan(Maths::ToRadians(0.5f * foV))) / aspectRatio;
	matrix.Elements[1 + 1 * 4] = 1.0f / ::tan(Maths::ToRadians(0.5f * foV));
	matrix.Elements[2 + 2 * 4] = (near + far) / (near - far);
	matrix.Elements[2 + 3 * 4] = -1.f;
	matrix.Elements[3 + 2 * 4] = (2.f * near * far) / (near - far);

	return matrix;
}


