#pragma once

#include <Gene/GML/TokenTypes.hpp>

#include <variant>
#include <string>
#include <iostream>

namespace Gene {
	namespace GML {
		typedef std::variant<int, float, std::string, char> Variant;

		class Token {
		private:
			TokenType m_Type;

			Variant m_Value;

		public:
			template <typename T>
            static Token Create(TokenType type, T value)
			{
                Token tok;
                tok.m_Type = type;
                tok.m_Value = value;
                return tok;
			}

			void Print()
			{
				std::visit([=](auto&& e) {
					std::cout << "Token: Type ID {" << (int)m_Type << "}, Value {" << e << "}" << std::endl;
				}, m_Value);
			}

            inline TokenType Type() const { return m_Type; }
            inline Variant Value() const { return m_Value; }
		};
	}
}
