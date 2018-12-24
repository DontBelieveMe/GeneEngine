// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Platform/IWindow.hpp>

#include <Windows.h>

namespace g2 { namespace win32 {
	class Win32Window : public IWindow {
	public:
		Win32Window(const WindowConfig& config);

		virtual void Show() override;
		virtual void PollEvents() override;
	
	protected:
		virtual void Init() override;
	
	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	private:
		HWND m_hwnd;

		static const char CLASS_NAME[];
		static const char HWND_WINDOW_PTR_PROPERTY[];
	};
}}