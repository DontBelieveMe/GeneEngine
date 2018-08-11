// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#pragma once

#include <Math/Vector3.h>
#include <Graphics/Color.h>

namespace gene {
	namespace graphics {
		class Particle {
		public:
			Vector3 Position, Velocity;
			Color Colour;
			float Life;

			bool Alive;
		private:
		};
	}
}