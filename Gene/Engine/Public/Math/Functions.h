// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <type_traits>

namespace Gene {
	struct Maths
	{
		static constexpr float PI = 3.14159265359f;

		template <typename T>
		static T Clamp(T value, T min, T max) 
		{
			static_assert(std::is_arithmetic<T>::value, "ToRadians<T> requires arithmetic/numeric type");

			return (value < min) ? min : (value > max) ? max : value;
		}

		template <typename T>
		static T ToRadians(T degrees)
		{
			static_assert(std::is_arithmetic<T>::value, "ToRadians<T> requires arithmetic/numeric type");

			static constexpr float piOverOneEighty = Maths::PI / 180;
			return degrees * piOverOneEighty;
		}

		template <typename T>
		static T ToDegrees(T radians)
		{
			static_assert(std::is_arithmetic<T>::value, "ToRadians<T> requires arithmetic/numeric type");

			static constexpr float oneEightyOverPi = 180 / Maths::PI;
			return radians * oneEightyOverPi;
		}

        template <typename T> 
        static int Sign(const T& val) {
            return (T(0) < val) - (val < T(0));
        }
	};
}