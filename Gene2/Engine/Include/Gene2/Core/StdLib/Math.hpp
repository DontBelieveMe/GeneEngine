// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <cmath>

namespace g2 {
	struct Math {
		static inline float InvSqrt(const float& in) { return 1.0f / Sqrt(in); }
		static inline float Sqrt(const float& in) { return std::sqrt(in); }
		
		static inline float Sin(const float& in) { return std::sinf(in); }
		static inline float Cos(const float& in) { return std::cosf(in); }
		static inline float Tan(const float& in) { return std::tanf(in); }
	};
}