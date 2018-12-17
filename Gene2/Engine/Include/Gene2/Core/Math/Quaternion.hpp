// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Core/Math/Vector3.hpp>

namespace g2 {
	class Quaternion {
	public:
		float X, Y, Z, W;

		Quaternion(const Vector3& n, float a);
	};
}