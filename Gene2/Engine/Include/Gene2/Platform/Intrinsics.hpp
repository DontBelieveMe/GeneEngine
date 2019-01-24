// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Platform/PlatformInfo.hpp>

#ifdef G2_COMPILER_MSVC 
	#define G2_DEBUG_BREAK() __debugbreak()
	#define G2_FORCEINLINE __forceinline
#else
	#ifdef G2_COMPILER_GNUC
		#define G2_FORCEINLINE __attribute__((always_inline)) 
	#endif

	#define G2_DEBUG_BREAK()
#endif

#define G2_MARK_VARIABLE_UNUSED(x) (void)x
