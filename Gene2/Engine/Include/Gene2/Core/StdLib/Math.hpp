// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <cmath>

#include <Gene2/Platform/Intrinsics.hpp>

namespace g2 {
	struct Math {
		static G2_FORCEINLINE float Sqrt(const float& in) { return std::sqrt(in); }
		static G2_FORCEINLINE float InvSqrt(const float& in) { return 1.0f / Sqrt(in); }
		
		static G2_FORCEINLINE float Sin(const float& in) { return std::sinf(in); }
		static G2_FORCEINLINE float Cos(const float& in) { return std::cosf(in); }
		static G2_FORCEINLINE float Tan(const float& in) { return std::tanf(in); }

		static G2_FORCEINLINE float ACos(const float& in) { return std::acosf(in); }
		static G2_FORCEINLINE float ASin(const float& in) { return std::asinf(in); }
		static G2_FORCEINLINE float ATan(const float& in) { return std::atanf(in); }
		static G2_FORCEINLINE float ATan2(const float& a, const float& b) { return std::atan2f(a, b); }

		static G2_FORCEINLINE float Abs(const float& in) { return std::fabsf(in); }

		static inline float DegreesToRadians(const float& degrees) { return (Math::Pi / 180.f) * degrees; }
		static inline float RadiansToDegrees(const float& radians) { return (180.f / Math::Pi) * radians; }

		static inline float Clamp(const float& x, const float& min, const float& max)
		{
			return x < min ? min : x > max ? max : x;
		}

		static const float Pi;
	};
}