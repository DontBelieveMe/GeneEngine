#include <Math/Matrix4.h>
#include <string.h>

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