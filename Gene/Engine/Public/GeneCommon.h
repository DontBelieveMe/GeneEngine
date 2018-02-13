#pragma once
#include <assert.h>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>

#include <Platform/OS.h>

#ifdef GENE_COMPILER_MSVC
	#define GE_FORCEINLINE __forceinline
#else
	#define GE_FORCEINLINE inline
#endif

#define GE_ASSERT(cond, ...) \
	do { \
		if(!(cond)){ \
			logf(__VA_ARGS__); \
			assert(cond); \
		} \
	} while(0) \

GE_FORCEINLINE void logf() {}

template <typename T, typename... Args>
GE_FORCEINLINE void logf(const char *t, T arg, Args... args)
{
    printf(t, arg, args...);
}

GE_FORCEINLINE void logf(const char *t)
{
    printf("%s", t);
}

namespace Gene { 
    typedef unsigned char  byte;
    typedef unsigned char  uint8;
    typedef char           int8;
    typedef unsigned short uint16;
    typedef short          int16;
    typedef unsigned int   uint32;
    typedef int            int32;
    
    template <typename T>
    using Array = std::vector<T>;
}
