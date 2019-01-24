// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Platform/IWindow.hpp>
#include <Gene2/Platform/PlatformInfo.hpp>

using namespace g2;

IWindow::IWindow(const WindowConfig& config)
	: m_config(config), m_bOpen(false)
{
}

void* IWindow::GetHandle() const {
	return m_handle;
}

bool IWindow::PollEvent(Event& event)
{
	if (m_eventQueue.empty())
	{
		this->ProcessPlatformEvents();
	}

	if (!m_eventQueue.empty())
	{
		event = m_eventQueue.front();
		m_eventQueue.pop();

		return true;
	}

	return false;
}

#ifdef G2_PLATFORM_WINDOWS
	#include <Gene2/Platform/Windows/Win32Window.hpp>
	typedef win32::Win32Window PlatformWindow;
#elif defined(G2_PLATFORM_LINUX)
	#include <Gene2/Platform/Linux/X11Window.hpp>
	typedef x11::X11Window PlatformWindow;
#else
	#error Selected Windowing Module not currently supported
#endif

SharedPtr<IWindow> IWindow::Create(const WindowConfig& windowConfig)
{
	const SharedPtr<IWindow> window = g2::MakeShared<PlatformWindow>(windowConfig);
	window->Init();

	return window;
}
