// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Platform/Window.h>
#include <Input/KeyboardState.h>

namespace gene { namespace input {
	class Keyboard
	{
	private:
		static platform::Window *s_PrimaryWindow;
		friend class platform::Window;
	
	public:
		static void SetPrimaryWindow(platform::Window *window);
		static KeyboardState& GetState();

        static char KeyToASCII(Keys key);
	};
}}