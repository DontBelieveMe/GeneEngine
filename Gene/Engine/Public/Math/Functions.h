#pragma once

namespace Gene { namespace Math {
	struct Maths
	{
		static constexpr float PI = 3.14159265359f;

		template <typename T>
		static T Clamp(T value, T min, T max) 
		{
			return (value < min) ? min : (value > max) ? max : value;
		}

		template <typename T>
		static T ToRadians(T degrees)
		{
			static constexpr float piOverOneEighty = Maths::PI / 180;
			return degrees * piOverOneEighty;
		}

		template <typename T>
		static T ToDegrees(T radians)
		{
			static constexpr float oneEightyOverPi = 180 / Maths::PI;
			return radians * oneEightyOverPi;
		}
	};
}}