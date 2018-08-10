// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once
#include <assert.h>
#include <iterator>
#include <string>
#include <sstream>

#include <Platform/OS.h>
#include <Debug/Logger.h>

#if defined(GENE_COMPILER_MSVC)
	#define GE_FORCEINLINE __forceinline
    #define VS_BREAK_IF(cond) do{if(cond)__debugbreak();}while(0)
#elif defined(GENE_COMPILER_GNUC)
    #define GE_FORCEINLINE inline __attribute__((always_inline))
#define VS_BREAK_IF(cond)
#else
	#define GE_FORCEINLINE inline
    #define VS_BREAK_IF(cond)
#endif

#define GE_ASSERT(cond, ...) \
	do { \
		if(!(cond)){ \
            LOG(gene::LogLevel::Assert, __VA_ARGS__);\
            assert(cond); \
		} \
	} while(0)

namespace gene { 
    typedef unsigned char  byte;
    typedef unsigned char  uint8;
    typedef char           int8;
    typedef unsigned short uint16;
    typedef short          int16;
    typedef unsigned int   uint32;
    typedef int            int32;

	inline bool CompareFloat(float a, float b) {
		return (fabs(a - b) < 0.005f);
	}
}
