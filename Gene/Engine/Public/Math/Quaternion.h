#pragma once

#include "Vector3.h"

namespace Gene {
	namespace Math {
		class Quaternion {
		public:
			float X, Y, Z, W;

			Quaternion(const Vector3& n, float a);
		};
	}

	typedef Math::Quaternion Quaternion;
}