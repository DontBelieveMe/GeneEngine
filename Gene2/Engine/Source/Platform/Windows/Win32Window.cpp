// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Gene2/Platform/Windows/Win32Window.hpp>
#include <Gene2/Debug/Logging.hpp>

#include <Gene2/Debug/Assert.hpp>

using namespace g2;
using namespace g2::win32;

const char Win32Window::CLASS_NAME[] = "Gene2Window";

LRESULT CALLBACK Win32Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Win32Window::Win32Window(const WindowConfig& config)
	: IWindow(config) {}

void Win32Window::Init()
{
	const HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASSEX wndClass    = { 0 };
	wndClass.cbClsExtra    = 0;
	wndClass.cbSize        = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra    = 0;
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon         = nullptr;
	wndClass.hIconSm       = nullptr;
	wndClass.hInstance     = hInstance;
	wndClass.lpfnWndProc   = (WNDPROC)WndProc;
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.lpszMenuName  = nullptr;
	wndClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	const ATOM registerClassResult = RegisterClassEx(&wndClass);

	G2_ASSERT(
		registerClassResult != 0, 
		"Could not register Win32 window class. Win32 Error {0}", GetLastError()
	);

	const DWORD style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

	RECT adjustedRect;
	adjustedRect.left   = 0;
	adjustedRect.top    = 0;
	adjustedRect.right  = m_config.Width;
	adjustedRect.bottom = m_config.Height;

	m_hwnd = CreateWindowEx(
		0, CLASS_NAME, m_config.Title.c_str(),
		style, 
		200, 200, 
		adjustedRect.right - adjustedRect.left,
		adjustedRect.bottom - adjustedRect.top,
		nullptr, nullptr,
		hInstance,
		nullptr
	);
	G2_ASSERT(
		m_hwnd != nullptr, 
		"Could not create Win32 window. Win32 Error {0}", GetLastError()
	);
}

void Win32Window::Show()
{
	m_bOpen = true;
	SetForegroundWindow(m_hwnd);
	ShowWindow(m_hwnd, SW_SHOW);
}

void Win32Window::PollEvents()
{
	MSG msg;
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			m_bOpen = false;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
