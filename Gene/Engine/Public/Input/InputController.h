// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Input/Keys.h>
#include <Math/Vector2.h>
#include <string.h>

namespace gene { namespace input {
    
    class KeyDevice {
    public:
        KeyDevice() {
            memset(m_keyMap, 0, 62256);
        }

        bool IsKeyPressed(const Keys& key);
        void PressKeyDown(const Keys& key);
        void ReleaseKeyDown(const Keys& key);
        
		Key *GetKeyMap() { return m_keyMap; }

		static bool IsKeyDownInMap(Key *map, Keys key) {
			return map[static_cast<int>(key)];
		}

    private:
        Key m_keyMap[62256];
    };
    
    class TouchDevice { 
    };
    
    enum MouseButton {
        Left = 1, 
        Right = 2, 
        Middle = 4, 
        None = 16
    };

    class MouseDevice {
    public:
        /*enum class Button {
            Left = 1, Right = 2, Middle = 4, None = 16
        };*/
    
        const Vector2i& GetCursorPosition() const { return m_cursorPosition; }
        
        bool IsButtonDown(const MouseButton& button);
        MouseButton GetRawButtonState() { return m_buttonState; }
        
        /** Primary for OS API use - may not work, as the platform window manager will probably snap the mouse position back to the correct one. */
        void TrySetCursorPosition(const Vector2i& pos);
        
        /** Primary for OS API use - may not work, as the platform window manager will probably snap state back to the correct one. */
        void TrySetButtonState(const MouseButton& button);
        
    private:
        Vector2i m_cursorPosition;
        MouseButton m_buttonState = MouseButton::None;
    };
    
    class InputController 
    {
    public:
        
        KeyDevice *GetKeyDevice() { return &m_keyDevice; }
        TouchDevice *GetTouchDevice() { return &m_touchDevice; }
        MouseDevice *GetMouseDevice() { return &m_mouseDevice; }
        
    private:
        KeyDevice m_keyDevice;
        TouchDevice m_touchDevice;
        MouseDevice m_mouseDevice;
    };
}}
