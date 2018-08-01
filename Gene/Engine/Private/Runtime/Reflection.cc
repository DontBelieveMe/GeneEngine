#include <Runtime/Reflection.h>

META_DEFINE_BASIC_START
    META_DEFINE_BASIC_TYPE(char)
    META_DEFINE_BASIC_TYPE(signed char)
    META_DEFINE_BASIC_TYPE(unsigned char)

    META_DEFINE_BASIC_TYPE(int)
    META_DEFINE_BASIC_TYPE(signed int)
    META_DEFINE_BASIC_TYPE(unsigned int)
    META_DEFINE_BASIC_TYPE(unsigned)

    META_DEFINE_BASIC_TYPE(short int)
    META_DEFINE_BASIC_TYPE(unsigned short int)
    META_DEFINE_BASIC_TYPE(signed short int)
    META_DEFINE_BASIC_TYPE(short)

    META_DEFINE_BASIC_TYPE(float)
    META_DEFINE_BASIC_TYPE(double)
    META_DEFINE_BASIC_TYPE(long double)
    
    META_DEFINE_BASIC_TYPE(bool)
    
    META_DEFINE_BASIC_TYPE(long)
    META_DEFINE_BASIC_TYPE(long int)
    META_DEFINE_BASIC_TYPE(signed long int)
    META_DEFINE_BASIC_TYPE(unsigned long int)
    META_DEFINE_BASIC_TYPE(long long)

    META_DEFINE_BASIC_TYPE(wchar_t)
META_DEFINE_BASIC_END

namespace meta {
    void MetaDataRegistry::DefaultRegistrations()
    {
        __s_metaDataInstance__.Init();
        LibraryRegistrations();
    }
}