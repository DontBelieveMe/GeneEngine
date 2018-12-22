// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Gene2/Platform/IWindow.hpp>
#include <Gene2/Platform/PlatformInfo.hpp>

using namespace g2;

IWindow::IWindow(const WindowConfig& config)
	: m_config(config), m_bOpen(false)
{
}

#ifdef G2_PLATFORM_WINDOWS
	#include <Gene2/Platform/Windows/Win32Window.hpp>
#endif

IWindow* IWindow::Create(const WindowConfig& windowConfig)
{
	IWindow* window = nullptr;

#ifdef G2_PLATFORM_WINDOWS
	window = new win32::Win32Window(windowConfig);
#endif

	window->Init();

	return window;
}