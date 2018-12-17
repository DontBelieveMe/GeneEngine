#include <Gene2/Core/StdLib/String.hpp>
#include <iostream>

int main()
{
	g2::String s = "dave";
	g2::String str = g2::FormatString("{0} says hello! (that was {0}, who is {1} years old)\nbtw, escapes {{0} also work", s, 53);

	std::cout << str << std::endl;
	
	system("pause");
    return 0;
}