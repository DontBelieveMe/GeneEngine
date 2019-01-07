// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Platform/IWindow.hpp>
#include <Gene2/Input/Keys.hpp>

#define WIN32_LEAN_AND_MEAN
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
		/**
		 * @brief Win32 callback for processing messages.
		 * @param hWnd A handle to the window
		 * @param msg The message
		 * @param wParam Additional message information. The contents of this parameter depend on the msg.
		 * @param lParam Additional message information. The contents of this parameter depend on the msg.
		 * @return The result of message processing and depends on the event
		 */
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		/**
		 * @brief Process a single Win32 event.
		 * @param msg The message.
		 * @param wParam Additional message information. The contents of this parameter depend on the msg.
		 * @param lParam Additional message information. The contents of this parameter depend on the msg.
		 * @return True if the event has been handled, false if not.
		 */
		bool ProcessEvent(UINT msg, WPARAM wParam, LPARAM lParam);
		
		/**
		 * @brief Set's an event's key modifiers (ctrl, alt, shift, etc...)
		 * @param e The event
		 */
		void SetKeyEventModifiers(Event& e);
		
		/**
		 * @brief Convert a Win32 virtual key code to a Gene2 key code.
		 * @param key The Win32 virtual key code.
		 * @param flags The the lParam extra message info.
		 * @return The Gene2 equivalent of the specified Win32 key
		 */
		EKeyCode ConvertWin32KeyToG2Key(UINT key, LPARAM flags);

	private:
		HWND m_hwnd;

		static const char CLASS_NAME[];
		static const char HWND_WINDOW_PTR_PROPERTY[];
	};
}}