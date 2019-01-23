// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/RenderDevice.hpp>

using namespace g2;

#include <Gene2/Platform/PlatformInfo.hpp>

#ifdef G2_PLATFORM_WINDOWS
#include <Gene2/Graphics/Windows/Win32OpenGL3Context.hpp>
typedef win32::Win32OpenGL3Context PlatformContext;
#else
	#error No rendering support for non-Windows platforms!
#endif

void RenderDevice::Init(const g2::SharedPtr<IWindow>& window) 
{
	void* windowHandle = window->GetHandle();

	m_context = new PlatformContext(windowHandle);
	m_context->Create();
}

Buffer* RenderDevice::CreateBuffer(size_t initFlags)
{
	Buffer* buff = new Buffer;
	buff->Create(initFlags);
	return buff;
}