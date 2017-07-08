#pragma once
#include <assert.h>
#include <vector>

#define GE_ASSERT(cond) \
	assert(cond)

namespace Gene { 

    template <typename T>
    inline std::vector<T> MixVectors(const std::vector<T>& a, const std::vector<T>& b, int sampleRate, int sampleSize)
    {
        GE_ASSERT(a.size() == b.size());

        std::vector<T> out;
        for(int i = 0; i < a.size(); i += sampleRate) 
        {
            for(int j = 0; j < sampleSize; j++) 
            {
                out.push_back(a[i + j]);
            } 
            for(int j = 0; j < sampleSize; j++) 
            {
                out.push_back(b[i + j]);
            }
        }

        return out;
    }
}
