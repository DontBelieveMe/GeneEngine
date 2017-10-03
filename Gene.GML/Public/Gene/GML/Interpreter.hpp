#pragma once

#include <string>

#include <Gene/GML/Parser.hpp>
#include <Gene/GML/Token.hpp>
#include <Gene/GML/AbstractSyntaxTree.hpp>

namespace Gene {
	namespace GML {
		class Interpreter 
		{
		public:
			Interpreter(const std::string& source);
			~Interpreter();

            void Interpret();
        private:
            void ParseStatement();
            void ParseAssignment();

            void ParseExpression();
            void ParseTerm();
            void ParseFactor();

		private:
            Parser  *m_Parser;
            Token    m_CurrentToken;
        };
	}
}
