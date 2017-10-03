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
			Token(TokenType type, T value)
			{
				m_Type = type;
				m_Value = value;
			}

			void Print()
			{
				std::visit([=](auto&& e) {
					std::cout << "Token: Type ID {" << (int)m_Type << "}, Value {" << e << "}" << std::endl;
				}, m_Value);
			}

			inline TokenType Type() const {
				return m_Type;
			}

			inline const Variant& Variant() const {
				return m_Value;
			}
		};
	}
}