#pragma once

#include <Gene/GML/Token.hpp>

namespace Gene {
	namespace GML {
		class Parser
		{
		private:
			std::string m_Source;
			int m_Index;
			Token ConstructSingleToken(char& actual, TokenType type);

		public:
			Parser(const std::string& source);

			Token GetNextToken();
		};
	}
}