#pragma once

namespace Gene { namespace Math {
	struct MathFunctions
	{
		template <typename T>
		static T Clamp(T value, T min, T max) 
		{
			return (value < min) ? min : (value > max) ? max : value;
		}
	};
}}