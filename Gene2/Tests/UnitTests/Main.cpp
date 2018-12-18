#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

int main(int argc, char* argv[])
{
	Catch::Session session;

	int result = session.run();

	return result;
}