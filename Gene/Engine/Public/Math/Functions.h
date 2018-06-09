// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <type_traits>
#include <math.h>

namespace gene {
	struct Maths
	{
		static constexpr float PI = 3.14159265359f;

        static float Sqrt(float v) {
            return sqrtf(v);
        }

        static float Sin(float v) {
            return sinf(v);
        }

        static float Asin(float v) {
            return asinf(v);
        }

        static float Cos(float v) {
            return cosf(v);
        }

        static float Acos(float v) {
            return acosf(v);
        }

        static float Tan(float v) {
            return tanf(v);
        }

        static float Atan(float v) {
            return atanf(v);
        }

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