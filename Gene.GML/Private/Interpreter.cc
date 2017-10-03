#include <Gene/GML/Interpreter.hpp>

using namespace Gene::GML;

Interpreter::Interpreter(const std::string& source)
{
	m_Parser = new Parser(source);
}

Interpreter::~Interpreter()
{
	delete m_Parser;
}