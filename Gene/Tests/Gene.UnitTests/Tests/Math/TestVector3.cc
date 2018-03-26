#include <Catch/catch.hpp>

#include <Math/Vector3.h>

#include <math.h>

using namespace Gene;

TEST_CASE("Vector3 sets floating point values to zero when not specified in constructor", "[Vector3]") 
{
	Vector3 vec3;

	REQUIRE(vec3.X == Approx(0.f));
	REQUIRE(vec3.Y == Approx(0.f));
	REQUIRE(vec3.Z == Approx(0.f));
}

TEST_CASE("Vector3 sets xyz components to constructor specified values", "[Vector3]")
{
	Vector3 vec3(123.5f, 1.f, -90.83f);

	REQUIRE(vec3.X == Approx(123.5f));
	REQUIRE(vec3.Y == Approx(1.f));
	REQUIRE(vec3.Z == Approx(-90.83f));
}

TEST_CASE("Vector3 addition provides correct xyz components using overload operator+", "[Vector3]")
{
	Vector3 a(1, 2, 3);
	Vector3 b(3.5f, 2.4f, 1.3f);
	Vector3 result = a + b;

	REQUIRE(result.X == Approx(a.X + b.X));
	REQUIRE(result.Y == Approx(a.Y + b.Y));
	REQUIRE(result.Z == Approx(a.Z + b.Z));
}

TEST_CASE("Vector3 subtraction provides correct xyz components using overload operator-()", "[Vector3]")
{
	Vector3 a(10, 20, 30);
	Vector3 b(3.5f, 2.4f, 1.3f);
	Vector3 result = a - b;

	REQUIRE(result.X == Approx(a.X - b.X));
	REQUIRE(result.Y == Approx(a.Y - b.Y));
	REQUIRE(result.Z == Approx(a.Z - b.Z));
}

TEST_CASE("Vector3 static Normalize() method correctly normalizes input vector", "[Vector3]")
{
	Vector3 inputVector(1.f, 2.f, 3.f);

	Vector3 normalizedVector = Vector3::Normalize(inputVector);

	float magnitude = sqrt(powf(1.f, 2) + powf(2.f, 2) + powf(3.f, 2));
	float expectedX = 1.f / magnitude;
	float expectedY = 2.f / magnitude;
	float expectedZ = 3.f / magnitude;

	REQUIRE(normalizedVector.X == Approx(expectedX));
	REQUIRE(normalizedVector.Y == Approx(expectedY));
	REQUIRE(normalizedVector.Z == Approx(expectedZ));
}

TEST_CASE("Vector3 in-place/class method Normalize() correctly normalizes vector", "[Vector3]")
{
	float inputX = 1.f,
		  inputY = 2.f,
		  inputZ = 3.f;

	Vector3 normalizedVector(inputX, inputY, inputZ);
	normalizedVector.Normalize();

	float magnitude = sqrt(powf(inputX, 2) + powf(inputY, 2) + powf(inputZ, 2));
	float expectedX = inputX / magnitude;
	float expectedY = inputY / magnitude;
	float expectedZ = inputZ / magnitude;

	REQUIRE(normalizedVector.X == Approx(expectedX));
	REQUIRE(normalizedVector.Y == Approx(expectedY));
	REQUIRE(normalizedVector.Z == Approx(expectedZ));
}

TEST_CASE("Vector3 static method Negate correct negates xyz components", "[Vector3]")
{
	Vector3 inputVector(76.f, 89.f, 47.46f);
	Vector3 negatedVector = Vector3::Negate(inputVector);

	REQUIRE(negatedVector.X == Approx(-76.f));
	REQUIRE(negatedVector.Y == Approx(-89.f));
	REQUIRE(negatedVector.Z == Approx(-47.46f));
}

TEST_CASE("Vector3 CrossProduct static method returns correct vector", "[Vector3]")
{
	Vector3 inputVectorA(2.f, 3.f, 4.f);
	Vector3 inputVectorB(5.f, 6.f, 7.f);

	float expectedX = (inputVectorA.Y * inputVectorB.Z) - (inputVectorA.Z * inputVectorB.Y);
	float expectedY = (inputVectorA.Z * inputVectorB.X) - (inputVectorA.X * inputVectorB.Z);
	float expectedZ = (inputVectorA.X * inputVectorB.Y) - (inputVectorA.Y * inputVectorB.X);

	Vector3 computedCrossProduct = Vector3::CrossProduct(inputVectorA, inputVectorB);

	REQUIRE(computedCrossProduct.X == Approx(expectedX));
	REQUIRE(computedCrossProduct.Y == Approx(expectedY));
	REQUIRE(computedCrossProduct.Z == Approx(expectedZ));
}

TEST_CASE("Vector3 DotProduct static method returns correct scalar value", "[Vector3]")
{
	Vector3 inputVectorA(56.f, 78.f, 567.f);
	Vector3 inputVectorB(2344.f, 123.f, -123.f);

	float expectedResult = (inputVectorA.X * inputVectorB.X) + 
						   (inputVectorA.Y * inputVectorB.Y) +
						   (inputVectorA.Z * inputVectorB.Z);

	float actualComputedDotProduct = Vector3::DotProduct(inputVectorA, inputVectorB);

	REQUIRE(actualComputedDotProduct == Approx(expectedResult));
}

TEST_CASE("Vector3 member method Length() returns correct magnitude for vector", "[Vector3]")
{
	Vector3 inputVector(1234.f, 765.f, 2.f);

	float expectedMagnitude = sqrt(powf(inputVector.X, 2) +
		powf(inputVector.Y, 2) +
		powf(inputVector.Z, 2));

	float actual = inputVector.Length();

	REQUIRE(actual == Approx(expectedMagnitude));
}