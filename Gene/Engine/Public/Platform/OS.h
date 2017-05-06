#pragma once

#ifdef _WIN32
	#define GENE_OS_WINDOWS
#elif __linux__
	#define GENE_OS_LINUX
#elif __APLE__ && __MACH__
	#define GENE_OS_MACOS
#endif
