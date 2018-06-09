// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Input/Keys.h>

namespace gene { namespace platform {
    // LOL -> Lets re predefine all our platform specific windows here :D
    namespace win32 { class Win32Window; }
    namespace X11 { class X11Window; }
}}

namespace gene { namespace input {
	struct KeyboardState
	{
    private:
        Key KeyMap[62256];

        friend class platform::win32::Win32Window;
        friend class platform::X11::X11Window;

    public:
        inline bool IsKeyDown(Keys key) const { return KeyMap[static_cast<int>(key)]; }
	};
}}
