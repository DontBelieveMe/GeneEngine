// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Input/Keyboard.hpp>

using namespace g2;

bool Keyboard::IsKeyDown(EKeyCode key)
{
	Keyboard* keyboard = Keyboard::GetInstance();
	return keyboard->m_state[static_cast<int>(key)];
}