// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#pragma once

namespace Gene {
	struct Vector2 
	{
		float X, Y;

		Vector2(float x, float y);
		Vector2();

		Vector2 operator+(const Vector2& b);
		Vector2 operator-(const Vector2& b);
	};
}