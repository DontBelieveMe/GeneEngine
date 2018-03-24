// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#pragma once

#include <Platform/Window.h>
#include <Input/KeyboardState.h>

namespace Gene { namespace Input {
	class Keyboard
	{
	private:
		static Platform::Window *s_PrimaryWindow;
		friend class Platform::Window;
	
	public:
		static void SetPrimaryWindow(Platform::Window *window);
		static KeyboardState& GetState();

        static char KeyToASCII(Keys key);
	};
}}