// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Input/Keys.hpp>
#include <Gene2/Core/Utility/Singleton.hpp>

namespace g2
{
	namespace win32 { class Win32Window; }

	class Keyboard : Singleton<Keyboard>
	{
	private:
		friend class win32::Win32Window;

		bool m_state[65536];

	public:
		static bool IsKeyDown(EKeyCode keyCode);
	};
}