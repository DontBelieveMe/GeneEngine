// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include "Vector3.h"

namespace gene {
	namespace math {
		class Quaternion {
		public:
			float X, Y, Z, W;

			Quaternion(const Vector3& n, float a);
		};
	}

	typedef math::Quaternion Quaternion;
}