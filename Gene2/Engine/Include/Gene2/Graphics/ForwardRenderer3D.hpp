// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include "RenderDevice.hpp" 

namespace g2
{
	class ForwardRenderer3D
	{
	public:
		void Render(RenderDevice* renderDevice, BufferArrayHandle vao, ShaderHandle shaders);
	};
}
