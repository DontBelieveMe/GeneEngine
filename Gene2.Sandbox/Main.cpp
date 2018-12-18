#include <Gene2/Core/StdLib/String.hpp>
#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Debug/Assert.hpp>

int main()
{
	g2::Logger::GetInstance()->AddRoute<g2::ConsoleLoggerRoute>();

	G2_TRACE("Hello World, trace {0}", "bob");
	G2_WARN("Warning!, {0}", 54);
	G2_ERROR("This is an error {0}, {1}, {2}", 123, "thing", 'p');

	G2_ASSERT(g2::FormatString("hello {0}", "dave") == "hello dave");

	g2::String s = "dave";
	g2::String str = g2::FormatString("\nformat string tests:\n{0} says hello! (that was {0}, who is {1} years old)\nbtw, escapes {{0} also work{", s, 53);

	G2_TRACE(str);

	system("pause");
    return 0;
}