#pragma once
#include <Platform/OS.h>
namespace Gene { namespace Input {
	typedef bool Key;
#ifdef GENE_OS_WINDOWS
    #include <Platform/Input/Win32Keys.h>
#else
    #ifdef GENE_OS_LINUX
        #include <Platform/Input/LinuxKeys.h>
    #endif
#endif
}}
