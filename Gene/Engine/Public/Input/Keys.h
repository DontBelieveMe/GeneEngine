// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Platform/OS.h>

namespace gene { namespace input {
	typedef bool Key;
#if defined(GENE_OS_WINDOWS)
    #include <Platform/Input/Win32Keys.h>
#elif defined(GENE_OS_LINUX)
    #include <Platform/Input/LinuxKeys.h>
#elif defined(GENE_OS_ANDROID)
	/*
		TODO:
			We need to think of a better way of disabling key input functionality for android
			(which doesn't really have it).
			We should provide an API to acess native keyboard at some point, but thats not critical functionality.
			This is just here to get the build working.
	*/
	#include <Platform/Input/AndroidKeys.h>
#endif
}}
