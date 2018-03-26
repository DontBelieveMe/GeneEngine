#include <Catch/catch.hpp>
#include <Math/Matrix4.h>

using namespace Gene;

static bool CompareMatrices(Matrix4 matrix, 
	float m00, float m10, float m20, float m30,
	float m01, float m11, float m21, float m31,
	float m02, float m12, float m22, float m32,
	float m03, float m13, float m23, float m33)
{
	bool c00 = matrix.Elements[0 + 0 * 4] == Approx(m00);
	bool c10 = matrix.Elements[1 + 0 * 4] == Approx(m10);
	bool c20 = matrix.Elements[2 + 0 * 4] == Approx(m20);
	bool c30 = matrix.Elements[3 + 0 * 4] == Approx(m30);
	bool c01 = matrix.Elements[0 + 1 * 4] == Approx(m01);
	bool c11 = matrix.Elements[1 + 1 * 4] == Approx(m11);
	bool c21 = matrix.Elements[2 + 1 * 4] == Approx(m21);
	bool c31 = matrix.Elements[3 + 1 * 4] == Approx(m31);
	bool c02 = matrix.Elements[0 + 2 * 4] == Approx(m02);
	bool c12 = matrix.Elements[1 + 2 * 4] == Approx(m12);
	bool c22 = matrix.Elements[2 + 2 * 4] == Approx(m22);
	bool c32 = matrix.Elements[3 + 2 * 4] == Approx(m32);
	bool c03 = matrix.Elements[0 + 3 * 4] == Approx(m03);
	bool c13 = matrix.Elements[1 + 3 * 4] == Approx(m13);
	bool c23 = matrix.Elements[2 + 3 * 4] == Approx(m23);
	bool c33 = matrix.Elements[3 + 3 * 4] == Approx(m33);

	bool compares = 
		c00 && c10 && c20 && c30 &&
		c01 && c11 && c21 && c31 &&
		c02 && c12 && c22 && c32 &&
		c03 && c13 && c23 && c33;
	return compares;
}

#define AssertMatrixElements(matrix, m00, m10, m20, m30, \
							 m01, m11, m21, m31, \
							 m02, m12, m22, m32, \
							 m03, m13, m23, m33 ) \
						REQUIRE(CompareMatrices(matrix, m00,m10,m20,m30, \
														  m01,m11,m21,m31, \
													      m02,m12,m22,m32, \
													      m03,m13,m23,m33))

TEST_CASE("Matrix4 element count is correct", "[Matrix4]")
{
	REQUIRE(Matrix4::ElementCount == 4 * 4);
}

TEST_CASE("Matrix4 default constructor initalizes to identity 1.f", "[Matrix4]")
{
	Matrix4 matrix;
	AssertMatrixElements(matrix, 
		1.f, 0,   0,   0,
		0,   1.f, 0,   0,
		0,   0,   1.f, 0,
		0,   0,   0,   1.f
	);
}

TEST_CASE("Matrix4 constructor implements identity matrix with given diagonal", "[Matrix4]")
{
	float diag = 5.7f;
	Matrix4 matrix(diag);
	AssertMatrixElements(matrix,
		diag, 0, 0, 0,
		0, diag, 0, 0,
		0, 0, diag, 0,
		0, 0, 0, diag
	);
}

TEST_CASE("Test Matrix4 initalization from matrix array", "[Matrix4]")
{
	float data[] = {
		10,   20,   30,    40,
		40,   50,   60,    70,
		2340, 0234, 0,     30,
		06,   07,   0234, -123
	};
	
	Matrix4 mat4(data);

	AssertMatrixElements(mat4,
		10,    20,   30,    40,
		40,    50,   60,    70,
		2340,  0234, 0,     30,
		06,    07,   0234, -123
	);
}

TEST_CASE("Matrix4 & Matrix4 multiplication via Multiply() method", "[Matrix4]")
{
	float mat1[] = {
		12.f, 34.f, 56.f, 78.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 67.f, 97.f,
		32.f, 54.f, 65.f, 777.f
	};

	float mat2[]{
		4,    5,     6,     7,
		123,  23,    1.2f,  8.f,
		33.f, 123.f, 123.f, 23213.f,
		4.f,  33.f, -23.f,  33.f
	};

	Matrix4 matA(mat1);
	Matrix4 matB(mat2);

	Matrix4 result = matA.Multiply(matB);
	AssertMatrixElements(result,
		6390.f,  10304.f,  5206.8f,           1302858.f,
		1677.f,  2024.f,   1143.f,            255882.f,
		4373.f,  11829.f,  6104.799f,         1558675.f,
		12023.f, 35038.f, -9619.2f,            1535142.f
	);
}

TEST_CASE("Matrix4 Vector3 translation via Translate() method", "[Matrix4]")
{
	Vector3 translation(10.f, -10.f, 4.5f);
	Matrix4 matrix;
	matrix.Translate(translation);

	AssertMatrixElements(matrix,
		1.f, 0.f, 0.f, 10.f,
		0.f, 1.f, 0.f, -10.f,
		0.f, 0.f, 1.f, 4.5f,
		0.f, 0.f, 0.f, 1.f
	);
}

TEST_CASE("Matrix4 Vector2 translation via Translate() method", "[Matrix4]")
{
	Vector2 translation(-67.5f, 10.f);
	Matrix4 matrix;
	matrix.Translate(translation);

	AssertMatrixElements(matrix,
		1.f, 0.f, 0.f, -67.5f,
		0.f, 1.f, 0.f, 10.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
}

TEST_CASE("Matrix4 Vector3 scale via Scale(Vector3) method", "[Matrix4]")
{
	Vector3 scale(10.f, -10.f, 4.5f);
	Matrix4 matrix;
	matrix.Scale(scale);

	AssertMatrixElements(matrix,
		10.f, 0.f, 0.f, 0.f,
		0.f, -10.f, 0.f, 0.f,
		0.f, 0.f, 4.5f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
}

TEST_CASE("Matrix4 Vector2 scale via Scale(Vector2) method", "[Matrix4]")
{
	Vector2 scale(4.5f, 92.7f);
	Matrix4 matrix;
	matrix.Scale(scale);

	AssertMatrixElements(matrix,
		4.5f, 0.f, 0.f, 0.f,
		0.f, 92.7f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
}

TEST_CASE("Matrix4 scale by given factor via Scale(float) method", "[Matrix4]")
{
	float scaleFactor = 56.f;
	Matrix4 matrix;
	matrix.Scale(scaleFactor);

	AssertMatrixElements(matrix,
		scaleFactor, 0.f, 0.f, 0.f,
		0.f, scaleFactor, 0.f, 0.f,
		0.f, 0.f, scaleFactor, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
}

TEST_CASE("Matrix4 rotation by angle (in degrees) along X axis using RotateX()", "[Matrix4]")
{
	float rotation = 23.f;
	Matrix4 matrix;
	matrix.RotateX(rotation);

	float radians = 0.401426f; // 23 degrees in radians

	AssertMatrixElements(matrix,
		1.f, 0.f,            0.f,            0.f,
		0.f, cos(radians),  sin(radians),  0.f,
		0.f, -sin(radians), cos(radians),  0.f,
		0.f, 0.f,            0.f,            1.f
	);
}

TEST_CASE("Matrix4 rotation by angle (in degrees) along Y axis using RotateY()", "[Matrix4]")
{
	float rotation = 45;
	Matrix4 matrix;
	matrix.RotateY(rotation);

	float radians = 0.785398f; // 45 degrees in radians

	AssertMatrixElements(matrix,
		cos(radians), 0.f, -sin(radians), 0.f,
		0.f,          1.f, 0.f,           0.f,
		sin(radians), 0.f, cos(radians),  0.f,
		0.f,          0.f, 0.f,           1.f
	);
}

TEST_CASE("Matrix4 rotation by angle (in degrees) along Z axis using RotateZ()", "[Matrix4]")
{
	float rotation = 195;
	Matrix4 matrix;
	matrix.RotateZ(rotation);

	float radians = 3.40339f; // 195 degrees in radians

	AssertMatrixElements(matrix,
		cos(radians),  sin(radians), 0.f, 0.f,
		-sin(radians), cos(radians), 0.f, 0.f,
		0.f,           0.f,          1.f, 0.f,
		0.f,		   0.f,          0.f, 1.f
	);
}

TEST_CASE("Matrix4 static Identity method defaults to diaganol 1", "[Matrix4]")
{
	Matrix4 mat4 = Matrix4::Identity();

	AssertMatrixElements(mat4,
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
}

TEST_CASE("Matrix4 static Identity() method allows a specified diaganol", "[Matrix4]")
{
	float diag = 346.f;
	Matrix4 mat4 = Matrix4::Identity(diag);

	AssertMatrixElements(mat4,
		diag, 0.f, 0.f, 0.f,
		0.f, diag, 0.f, 0.f,
		0.f, 0.f, diag, 0.f,
		0.f, 0.f, 0.f, diag);
}