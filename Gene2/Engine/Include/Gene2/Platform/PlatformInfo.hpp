// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#define G2_PLATFORM_WINDOWS

	#if defined(_WIN64)
		#define G2_CPU_64BIT
	#else
		#define G2_CPU_32BIT
	#endif
#else
#error Platform macros not implemented for non-Windows platforms.
#endif

#ifdef _MSC_VER
	#define G2_COMPILER_MSVC
#elif defined(__GNUC__)
	#define G2_COMPILER_GNUC
#endif