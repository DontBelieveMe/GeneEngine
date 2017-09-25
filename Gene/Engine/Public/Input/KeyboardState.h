#pragma once

#include <Input/Keys.h>

namespace Gene { namespace Input {
	struct KeyboardState
	{
		Key KeyMap[512];

        inline bool IsKeyDown(Keys key) const { return KeyMap[static_cast<int>(key)]; }
	};
}}
