#include <Gene/GML/Parser.hpp>

int main()
{
	using namespace Gene::GML;

	Parser parser("var pos = 1 + 1;");

	Token tok = parser.GetNextToken();
	while (tok.Type() != TokenType::EndOfFile) 
	{
		tok.Print();
		tok = parser.GetNextToken();
	}
}