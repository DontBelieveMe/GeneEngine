#pragma once

namespace Gene { namespace GML {
	enum class TokenType
	{
		Integer = 0,
		Add = 1, 
		Subtract = 2, 
		Multiply = 3, 
		Divide = 4,
		Identifier = 5,
		EndOfFile = 6,
		Semicolon = 7,
		Assignment = 8,
		None
	};
}}