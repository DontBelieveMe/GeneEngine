#pragma once

#include <Math/Vector2.h>
#include <Platform/Window.h>
#include <Input/MouseState.h>

namespace Gene { namespace Input {
	class Mouse {
	private:
		static Platform::Window *s_PrimaryWindow;
		friend class Platform::Window;

	public:
		static void SetPrimaryWindow(Platform::Window *window);

		static MouseState& GetState(); 
		static void SetPosition(const Vector2& pos);
	};
}}