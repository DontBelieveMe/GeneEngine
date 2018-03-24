// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#pragma once

#include <Input/Keys.h>

namespace Gene { namespace Input {
	struct KeyboardState
	{
        Key KeyMap[62256];

        inline bool IsKeyDown(Keys key) const { return KeyMap[static_cast<int>(key)]; }
	};
}}
