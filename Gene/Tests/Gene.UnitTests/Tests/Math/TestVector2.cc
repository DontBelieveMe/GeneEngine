#include <Catch/catch.hpp>

#include <Math/Vector2.h>

using namespace Gene;

TEST_CASE("Vector2 sets xy components to zero on default initalization", "[Vector2]")
{
	Vector2 vec2;

	REQUIRE(vec2.X == Approx(0.f));
	REQUIRE(vec2.Y == Approx(0.f));
}

TEST_CASE("Vector2 sets xy components to constructor specified components", "[Vector2]")
{
	Vector2 vec2(567.f, -78909.f);

	REQUIRE(vec2.X == Approx(567.f));
	REQUIRE(vec2.Y == Approx(-78909.f));
}

TEST_CASE("Vector2 addition operator+() calculates correct vector", "[Vector2]")
{
	Vector2 vecA(123.f, 345.f);
	Vector2 vecB(7.f, -23.4f);
	Vector2 result = vecA + vecB;

	REQUIRE(result.X == Approx(vecA.X + vecB.X));
	REQUIRE(result.Y == Approx(vecA.Y + vecB.Y));
}

TEST_CASE("Vector3 subtraction operator-() caculates correct resultant vector", "[Vector2]")
{
	Vector2 a(10, 20);
	Vector2 b(3.5f, 2.4f);
	Vector2 result = a - b;

	REQUIRE(result.X == Approx(a.X - b.X));
	REQUIRE(result.Y == Approx(a.Y - b.Y));
}