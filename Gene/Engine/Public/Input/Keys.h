#pragma once
#include <Platform/OS.h>
namespace Gene { namespace Input {
	typedef bool Key;
#if defined(GENE_OS_WINDOWS)
#include <Platform/Input/Win32Keys.h>
#elif defined(GENE_OS_LINUX)
#include <Platform/Input/LinuxKeys.h>
#endif
}}
