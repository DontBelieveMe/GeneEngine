// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <cmath>

#include <Gene2/Platform/Intrinsics.hpp>

namespace g2 {
	struct Math {
		static G2_FORCEINLINE float Sqrt(const float& in) { return std::sqrt(in); }
		static G2_FORCEINLINE float InvSqrt(const float& in) { return 1.0f / Sqrt(in); }
		
		static G2_FORCEINLINE float Sin(const float& in) { return std::sin(in); }
		static G2_FORCEINLINE float Cos(const float& in) { return std::cos(in); }
		static G2_FORCEINLINE float Tan(const float& in) { return std::tan(in); }

		static G2_FORCEINLINE float ACos(const float& in) { return std::acos(in); }
		static G2_FORCEINLINE float ASin(const float& in) { return std::asin(in); }
		static G2_FORCEINLINE float ATan(const float& in) { return std::atan(in); }
		static G2_FORCEINLINE float ATan2(const float& a, const float& b) { return std::atan2(a, b); }

		static G2_FORCEINLINE float Abs(const float& in) { return std::abs(in); }

		static inline float DegreesToRadians(const float& degrees) { return (Math::Pi / 180.f) * degrees; }
		static inline float RadiansToDegrees(const float& radians) { return (180.f / Math::Pi) * radians; }

		static inline float Clamp(const float& x, const float& min, const float& max)
		{
			return x < min ? min : x > max ? max : x;
		}

		static const float Pi;
	};
}
