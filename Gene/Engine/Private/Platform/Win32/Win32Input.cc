// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/OS.h>

#include <Input/Mouse.h>
#include <Input/MouseState.h>
#include <Input/Keyboard.h>
#include <Input/KeyboardState.h>

#include <Math/Vector2.h>

#include "Win32Window.h"

using namespace Gene::Input;
using namespace Gene;

#ifdef GENE_OS_WINDOWS
	#include <Windows.h>
	static MouseState& GetDefaultState()
	{
		static MouseState state;
		HWND activeWindow = GetActiveWindow();
		if (activeWindow == nullptr) return state;

		POINT cursor;
		GetCursorPos(&cursor);
		ScreenToClient(activeWindow, &cursor);
		state.Position.X = cursor.x;
		state.Position.Y = cursor.y;
		return state;
	}
	
	// Function definition for (static) Mouse::GetState (declaration in Input/Mouse.h)
	MouseState& Mouse::GetState()
	{
		if (s_PrimaryWindow == nullptr)
		{
			return GetDefaultState();
		}

		return s_PrimaryWindow->m_MouseState;
	}

	KeyboardState& Keyboard::GetState()
	{
		return s_PrimaryWindow->m_KeyState;
	}
	
	void Mouse::SetPosition(const Vector2i& pos)
	{
		HWND activeWindow = GetActiveWindow();
		RECT winRect;
		GetWindowRect(activeWindow, &winRect);

		SetCursorPos(winRect.left + pos.X, winRect.top + pos.Y);
	}
#endif
