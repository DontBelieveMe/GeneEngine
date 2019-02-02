// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/IOpenGL3Context.hpp>

using namespace g2;

#include <Gene2/Platform/PlatformInfo.hpp>

#ifdef G2_PLATFORM_WINDOWS
	#include <Gene2/Graphics/Windows/Win32OpenGL3Context.hpp>
	typedef win32::Win32OpenGL3Context PlatformContext;
#elif defined(G2_PLATFORM_LINUX)
	#include <Gene2/Graphics/Linux/X11OpenGL3Context.hpp>
	typedef x11::X11OpenGL3Context PlatformContext;
#else
	#error No rendering support for this platform! 
#endif

IOpenGL3Context* IOpenGL3Context::CreateContextForThisPlatform(void* windowHandle, ContextAttributes attributes)
{
	return new PlatformContext(windowHandle, attributes);
}