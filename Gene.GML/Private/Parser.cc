#include <Gene/GML/Parser.hpp>
#include <stdlib.h>

using namespace Gene::GML;

Parser::Parser(const std::string& source) : 
	m_Source(source),
	m_Index(0) {}

Token Parser::ConstructSingleToken(char& actual, TokenType type) 
{
	std::string str(1, actual);
	m_Index++;
	actual = m_Source[m_Index];
	Token tok(type, str);
	return tok;
}

Token Parser::GetNextToken() 
{
	char _char = m_Source[m_Index];

	while (_char == ' ' || _char == '\n') {
		m_Index++;
		_char = m_Source[m_Index];
	}

	if (_char == '\0') {
		Token tok(TokenType::EndOfFile, '\0');
		return tok;
	}

	if (isalpha(_char)) 
	{
		std::string tokenStr(1, _char);
		m_Index += 1;
		_char = m_Source[m_Index];
		
		while (isalpha(_char))
		{
			tokenStr += _char;
			m_Index++;
			_char = m_Source[m_Index];
		}

		Token tok(TokenType::Identifier, tokenStr);
		return tok;
	}

	if (isdigit(_char))
	{
		std::string tokenStr(1, _char);
		m_Index += 1;
		_char = m_Source[m_Index];

		while (isdigit(_char))
		{
			tokenStr += _char;
			m_Index++;
			_char = m_Source[m_Index];
		}
				
		Token tok(TokenType::Integer, atoi(tokenStr.c_str()));
		return tok;
	}

	if (_char == '=') return ConstructSingleToken(_char, TokenType::Assignment);
	if (_char == ';') return ConstructSingleToken(_char, TokenType::Semicolon);
	if (_char == '+') return ConstructSingleToken(_char, TokenType::Add);
	if (_char == '-') return ConstructSingleToken(_char, TokenType::Subtract);
}