#pragma once

// GENE_OS_ANDROID is a preproccessor variable that should be set by the complier
// As part of the build

#ifndef GENE_OS_ANDROID
	#ifdef _WIN32
		#define GENE_OS_WINDOWS
	#elif __linux__
		#define GENE_OS_LINUX
	#elif __APLE__ && __MACH__
		#define GENE_OS_MACOS
	#endif

	#ifdef _MSC_VER
		#define GENE_COMPILER_MSVC
	#endif
#endif