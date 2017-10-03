#pragma once

#include <string>
#include <Gene/GML/Parser.hpp>

namespace Gene {
	namespace GML {
		class Interpreter 
		{
		public:
			Interpreter(const std::string& source);
			~Interpreter();

		private:
			Parser *m_Parser;
		};
	}
}