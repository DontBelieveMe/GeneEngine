// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Input/Keys.hpp>

namespace g2 {
	struct KeyEvent
	{
		EKeyCode Key;
	};

	enum EEventType
	{
		EVENT_KEY,
		EVENT_QUIT,
	};

	struct Event
	{
		EEventType EventType;

		union
		{
			KeyEvent Key;
		};
	};
}