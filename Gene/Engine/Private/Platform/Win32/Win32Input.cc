#include <Platform/OS.h>
#include <Input/Mouse.h>
#include <Input/MouseState.h>
#include <Math/Vector2.h>
#include <Windows.h>

using namespace Gene::Input;

#ifdef GENE_OS_WINDOWS
	static MouseState& GetDefaultState()
	{
		static MouseState state;
		HWND activeWindow = GetActiveWindow();
		if (activeWindow == nullptr) return state;

		POINT cursor;
		GetCursorPos(&cursor);
		ScreenToClient(activeWindow, &cursor);
		state.Position.X = static_cast<float>(cursor.x);
		state.Position.Y = static_cast<float>(cursor.y);
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
#endif