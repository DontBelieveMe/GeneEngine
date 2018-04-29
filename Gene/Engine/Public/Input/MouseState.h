// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Math/Vector2.h>

namespace Gene {
    namespace Platform {
        // LOL -> Lets re predefine all our platform specific windows here :D (again)
        namespace Win32 { class Win32Window; }
        namespace X11 { class X11Window; }
    }
}

namespace Gene { namespace Input {
    enum class MouseButton {
        Left = 1, 
        Right = 2, 
        Middle = 4, 
        None = 16
    };

	struct MouseState {
    private:
		Vector2i m_Position;
        MouseButton m_Button;

        friend class Platform::Win32::Win32Window;
        friend class Platform::X11::X11Window;

    public:
        inline bool IsButtonDown(const MouseButton& button) {
            return static_cast<unsigned>(m_Button) & static_cast<unsigned>(button);
        }

        inline const Vector2i& GetPosition() const {
            return m_Position;
        }
	};
}}