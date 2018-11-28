// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <cmath>

namespace g2 {
	struct Math {
		static inline float Sqrt(const float& in) { return std::sqrt(in); }
		static inline float InvSqrt(const float& in) { return 1.0f / Sqrt(in); }
		
		static inline float Sin(const float& in) { return std::sinf(in); }
		static inline float Cos(const float& in) { return std::cosf(in); }
		static inline float Tan(const float& in) { return std::tanf(in); }

		static inline float ACos(const float& in) { return std::acosf(in); }
		static inline float ASin(const float& in) { return std::asinf(in); }
		static inline float ATan(const float& in) { return std::atanf(in); }
		static inline float ATan2(const float& a, const float& b) { return std::atan2f(a, b); }

		static inline float Abs(const float& in) { return std::fabsf(in); }

		static inline float DegreesToRadians(const float& degrees) { return (Math::Pi / 180.f) * degrees; }
		static inline float RadiansToDegrees(const float& radians) { return (180.f / Math::Pi) * radians; }

		static inline float Clamp(const float& x, const float& min, const float& max)
		{
			return x < min ? min : x > max ? max : x;
		}

		static const float Pi;
	};
}