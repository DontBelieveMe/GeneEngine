// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/OS.h>
#include <Input/Mouse.h>
#include <Input/MouseState.h>
#include <Input/Keyboard.h>
#include <Input/KeyboardState.h>

#include "AWindow.h"

using namespace Gene::Input;
using namespace Gene;

MouseState &Mouse::GetState()
{
    return s_PrimaryWindow->m_MouseState;
}

KeyboardState &Keyboard::GetState()
{
    return s_PrimaryWindow->m_KeyState;
}

void Mouse::SetPosition(const Vector2i &pos)
{
}
