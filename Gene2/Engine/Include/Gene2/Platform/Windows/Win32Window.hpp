// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Platform/IWindow.hpp>
#include <Gene2/Input/Keys.hpp>

#include <Windows.h>

namespace g2 { namespace win32 {
	class Win32Window : public IWindow {
	public:
		Win32Window(const WindowConfig& config);

		virtual void Show() override;
		virtual void ProcessPlatformEvents() override;
		virtual void Close() override;
	protected:
		virtual void Init() override;
	
	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
		bool ProcessEvent(UINT msg, WPARAM wParam, LPARAM lParam);
		void SetKeyEventModifiers(Event& e);
		EKeyCode ConvertWin32KeyToG2Key(UINT key);

	private:
		HWND m_hwnd;

		static const char CLASS_NAME[];
		static const char HWND_WINDOW_PTR_PROPERTY[];
	};
}}