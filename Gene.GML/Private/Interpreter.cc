#include <Gene/GML/Interpreter.hpp>
#include <variant>

using namespace Gene::GML;

Interpreter::Interpreter(const std::string& source)
{
	m_Parser = new Parser(source);

    m_CurrentToken = m_Parser->GetNextToken();
}

void Interpreter::Interpret()
{
    ParseExpression();
}

void Interpreter::ParseExpression()
{
    ParseTerm();
    while(m_CurrentToken.Type() == TokenType::Add || m_CurrentToken.Type() == TokenType::Subtract)
    {
        m_CurrentToken = m_Parser->GetNextToken();
        ParseTerm();
    }
}

void Interpreter::ParseTerm()
{
    std::cout << "Found term!" << std::endl;
    ParseFactor();
    while(m_CurrentToken.Type() == TokenType::Multiply || m_CurrentToken.Type() == TokenType::Divide)
    {
        m_CurrentToken = m_Parser->GetNextToken();
        ParseFactor();
    }
}

void Interpreter::ParseFactor()
{
    std::cout << "Factor!" << std::endl;
    m_CurrentToken = m_Parser->GetNextToken();
}

void Interpreter::ParseStatement()
{
}

void Interpreter::ParseAssignment()
{
}

Interpreter::~Interpreter()
{
	delete m_Parser;
}
