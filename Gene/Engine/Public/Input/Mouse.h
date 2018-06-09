// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Math/Vector2.h>
#include <Platform/Window.h>
#include <Input/MouseState.h>

namespace gene { namespace input {
	class Mouse {
	private:
		static platform::Window *s_PrimaryWindow;
		friend class platform::Window;

	public:
		static void SetPrimaryWindow(platform::Window *window);

		static MouseState& GetState(); 
		static void SetPosition(const Vector2i& pos);
	};
}}