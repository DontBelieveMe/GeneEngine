#pragma once
#include <assert.h>
#include <vector>

#include <Platform/OS.h>

#ifdef GENE_COMPILER_MSVC
	#define GE_FORCEINLINE __forceinline
#else
	#define GE_FORCEINLINE inline
#endif

#define GE_ASSERT(cond, ...) \
	do { \
		if(!cond){ \
			logf(__VA_ARGS__); \
			assert(cond); \
		} \
	} while(0) \

GE_FORCEINLINE void logf() {}

template <typename... Args>
GE_FORCEINLINE void logf(const char *t, Args... args)
{
	printf(t, args...);
}

namespace Gene { 
    typedef unsigned char  byte;
    typedef unsigned char  uint8;
    typedef char           int8;
    typedef unsigned short uint16;
    typedef short          int16;
    typedef unsigned int   uint32;
    typedef int            int32;
}
