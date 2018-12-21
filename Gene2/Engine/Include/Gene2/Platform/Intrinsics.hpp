// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#ifdef _MSC_VER 
	#define G2_DEBUG_BREAK() __debugbreak()
	#define G2_FORCEINLINE __forceinline
#else
	#ifdef __GNUC__
		#define G2_FORCEINLINE __attribute__((always_inline)) 
	#endif

	#define G2_DEBUG_BREAK()
	#error Intrinsics not supported on this platform
#endif