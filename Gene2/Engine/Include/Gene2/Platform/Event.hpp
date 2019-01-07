// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Input/Keys.hpp>
#include <Gene2/Input/Mouse.hpp>


namespace g2 {
	struct KeyEvent
	{
		EKeyCode Key;
		int Modifiers;
	};

	struct MouseEvent
	{
		EMouseButton Button;
	};

	enum EEventType
	{
		EVENT_KEYDOWN,
		EVENT_KEYUP,
		EVENT_QUIT,
		EVENT_MOUSEDOWN,
		EVENT_MOUSEUP,
	};

	struct Event
	{
		EEventType EventType;

		union
		{
			KeyEvent Key;
			MouseEvent Mouse;
		};
	};
}