#pragma once

#include <Input/Keys.h>

namespace Gene { namespace Input {
	struct KeyboardState
	{
		Key KeyMap[512];

		inline bool IsKeyDown(Keys key) { return KeyMap[static_cast<int>(key)]; }
	};
}}