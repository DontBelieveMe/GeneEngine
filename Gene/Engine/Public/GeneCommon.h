#pragma once
#include <assert.h>
#include <vector>

#define GE_ASSERT(cond) \
	assert(cond)

namespace Gene { 
    typedef unsigned char  byte;
    typedef unsigned char  uint8;
    typedef char           int8;
    typedef unsigned short uint16;
    typedef short          int16;
    typedef unsigned int   uint32;
    typedef int            int32;
}
