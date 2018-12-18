#include <Gene2/Core/StdLib/String.hpp>
#include <Gene2/Debug/Logging.hpp>

#include <iostream>

int main()
{
	G2_LOG("the logger said: 'oh, hey {0}'.", "dave");

	g2::String s = "dave";
	g2::String str = g2::FormatString("\nformat string tests:\n{0} says hello! (that was {0}, who is {1} years old)\nbtw, escapes {{0} also work{", s, 53);

	std::cout << str << std::endl;
	
	system("pause");
    return 0;
}