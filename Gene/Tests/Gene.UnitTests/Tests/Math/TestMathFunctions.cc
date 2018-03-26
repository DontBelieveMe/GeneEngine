#include <Catch/catch.hpp>

#include <Math/Functions.h>

using namespace Gene;

TEST_CASE("Test that noone has fiddled with PI (if you have, shame on you)", "[Functions]")
{
	REQUIRE(Maths::PI == Approx(3.14159265359f));
}

TEST_CASE("Test Clamp() clamping to minimum works.", "[MathFunctions]")
{
	int min = 12;
	int value = -123;
	int max = 56;
	int output = Maths::Clamp(value, min, max);

	REQUIRE(output == min);
}

TEST_CASE("Test Clamp() clamping to maximum works.", "[MathFunctions]")
{
	int min = 12;
	int value = 345;
	int max = 56;
	int output = Maths::Clamp(value, min, max);

	REQUIRE(output == max);
}

TEST_CASE("Test Clamp() works when no clamping required.", "[MathFunctions]")
{
	int min = 12;
	int value = 43;
	int max = 56;
	int output = Maths::Clamp(value, min, max);

	REQUIRE(output == value);
}

TEST_CASE("Test ToRadians converts degrees value correctly.", "[MathFunctions]")
{
	float degrees = 45;

	float expectedRadians = degrees * (Maths::PI / 180);

	REQUIRE(Maths::ToRadians(degrees) == Approx(expectedRadians));
}

TEST_CASE("Test ToDegrees converts radian value correctly.", "[MathFunctions]")
{
	float radians = 0.345f;

	float expectedDegrees = radians * (180 / Maths::PI);

	REQUIRE(Maths::ToDegrees(radians) == expectedDegrees);
}
