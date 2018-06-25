#pragma once

#include <Input/Keys.h>
#include <Math/Vector2.h>

namespace gene { namespace input {
    
    class KeyDevice {
    public:
        bool IsKeyPressed(const Keys& key);
        void PressKeyDown(const Keys& key);
        void ReleaseKeyDown(const Keys& key);
        
    private:
        Key m_keyMap[62256];
    };
    
    class TouchDevice { 
    };
    
    class MouseDevice {
    public:
        enum class Button {
            Left = 1, Right = 2, Middle = 4, None = 16
        };
    
        const Vector2i& GetCursorPosition() const { return m_cursorPosition; }
        
        bool IsButtonDown(const Button& button);
        Button GetRawButtonState() { return m_buttonState; }      
        
        /** Primary for OS API use - may not work, as the platform window manager will probably snap the mouse position back to the correct one. */
        void TrySetCursorPosition(Vector2i pos);
        
        /** Primary for OS API use - may not work, as the platform window manager will probably snap state back to the correct one. */
        void TrySetButtonState(const Button& button);
        
    private:
        Vector2i m_cursorPosition;
        Button m_buttonState = Button::None;
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
