// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/OS.h>
#include <Input/Mouse.h>
#include <Input/MouseState.h>
#include <Input/Keyboard.h>
#include <Input/KeyboardState.h>
#include <X11/X.h>

#include "X11Window.h"

using namespace Gene::Input;

MouseState &Mouse::GetState()
{
    return s_PrimaryWindow->m_MouseState;
}

KeyboardState &Keyboard::GetState()
{
    return s_PrimaryWindow->m_KeyState;
}

void Mouse::SetPosition(const Gene::Math::Vector2 &pos)
{
    using X11Window = Gene::Platform::X11::X11Window;
    X11Window *window = static_cast<X11Window*>(s_PrimaryWindow);
    window->SetPointerPosition(pos.X, pos.Y);
}
