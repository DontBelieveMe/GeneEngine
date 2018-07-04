// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Input/InputController.h>

using namespace gene::input;
using namespace gene;

bool KeyDevice::IsKeyPressed(const Keys& key)
{
    return m_keyMap[static_cast<int>(key)];
}

void KeyDevice::PressKeyDown(const Keys& key)
{
    m_keyMap[static_cast<int>(key)] = true;
}

void KeyDevice::ReleaseKeyDown(const Keys& key)
{
    m_keyMap[static_cast<int>(key)] = false;    
}

void MouseDevice::TrySetCursorPosition(const Vector2i& pos)
{
    m_cursorPosition.X = pos.X;
    m_cursorPosition.Y = pos.Y;
}

bool MouseDevice::IsButtonDown(const MouseButton& button)
{
    return static_cast<unsigned>(m_buttonState) & static_cast<unsigned>(button);
}

void MouseDevice::TrySetButtonState(const MouseButton& button)
{
    m_buttonState = button;
}