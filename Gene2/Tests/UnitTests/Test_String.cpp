#include <catch2/catch.hpp>

#include <Gene2/Core/StdLib/String.hpp>

TEST_CASE("FormatString passes through input with no format arguments", "[string]") 
{
	g2::String formatStringInput = "This is a plain string with no format arguments";
	g2::String formatStringOutput = g2::FormatString(formatStringInput);

	REQUIRE(formatStringInput == formatStringOutput);
}

TEST_CASE("FormatString substitutes multiple arguments", "[string]") 
{
	SECTION("Format arguments are specified in order and are valid") 
	{
		g2::String formatStringOutput = g2::FormatString("a={0},b={1},c={2}", "one", 2, '3');

		REQUIRE(formatStringOutput == "a=one,b=2,c=3");
	}

	SECTION("Format arguments are reused (e.g. multiple instance of one format input)") 
	{
		g2::String formatStringOutput = g2::FormatString("a={0},b={1},c={0}", "nine", 67);

		REQUIRE(formatStringOutput == "a=nine,b=67,c=nine");
	}

	SECTION("Format arguments count does not match used number of format inputs")
	{
		g2::String formatStringOutput = g2::FormatString("a={0},b={1},c={3}", 899, 'k');

		REQUIRE(formatStringOutput == "a=899,b=k,c=");
	}

	SECTION("Format inputs are out of order")
	{
		g2::String formatStringOutput = g2::FormatString("a={2},b={0},c={1}", 9, 10, 90);

		REQUIRE(formatStringOutput == "a=90,b=9,c=10");
	}
}

TEST_CASE("FormatString substitues one simple argument", "[string]") 
{
	g2::String formatStringInput = "FormatStringOutput = {0}, {0}";

	SECTION("Format argument is a string") 
	{
		g2::String formatStringOutput = g2::FormatString(formatStringInput, "dave");

		REQUIRE(formatStringOutput == "FormatStringOutput = dave, dave");
	}

	SECTION("Format argument is integer") 
	{
		g2::String formatStringOutput = g2::FormatString(formatStringInput, 538);

		REQUIRE(formatStringOutput == "FormatStringOutput = 538, 538");
	}

	SECTION("Format argument is not specified")
	{
		g2::String formatStringOutput = g2::FormatString(formatStringInput);
	
		REQUIRE(formatStringOutput == "FormatStringOutput = , ");
	}
}

