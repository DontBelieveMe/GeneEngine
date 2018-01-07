#include <Catch/catch.hpp>
#include <Graphics/Color.h>

using namespace Gene::Graphics;

TEST_CASE("Test color can store colors (range 0 -> 255) and output in format RGBA (range 0 -> 255)", "[Color]")
{
	Color color(255, 255, 143, 255);

	REQUIRE(color.R() == 255);
	REQUIRE(color.G() == 255);
	REQUIRE(color.B() == 143);
	REQUIRE(color.A() == 255);
}

TEST_CASE("Test color can store colors (range 0 -> 255) and output in format RGBA (range 0.f -> 1.f)", "[Color]")
{
	Color color(123, 255, 0, 255);

	REQUIRE(color.LinearR() == Approx(0.48235f));
	REQUIRE(color.LinearG() == Approx(1.f));
	REQUIRE(color.LinearB() == Approx(0.f));
	REQUIRE(color.LinearA() == Approx(1.f));
}
