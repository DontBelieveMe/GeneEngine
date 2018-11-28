#include <iostream>
#include <Gene2/Core/StdLib/Random.hpp>
#include <time.h>

int main()
{
	unsigned t = (unsigned int)time(NULL);
	std::cout << t << std::endl;
	g2::Random::Seed(t);
	std::cout << g2::Random::FloatRange(0.0f, 1.0f) << std::endl;

	system("pause");
    return 0;
}