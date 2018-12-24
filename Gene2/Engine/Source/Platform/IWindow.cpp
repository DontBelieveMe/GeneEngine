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
	typedef win32::Win32Window PlatformWindow;
#else
	#error Windowing Module not currently supported for non Windows backends.
#endif

SharedPtr<IWindow> IWindow::Create(const WindowConfig& windowConfig)
{
	SharedPtr<IWindow> window = g2::MakeShared<PlatformWindow>(windowConfig);
	window->Init();

	return window;
}