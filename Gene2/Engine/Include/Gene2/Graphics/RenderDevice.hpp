// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Graphics/IOpenGL3Context.hpp>
#include <Gene2/Platform/IWindow.hpp>
#include <Gene2/Graphics/Buffer.hpp>

namespace g2 {
	class RenderDevice {
	private:
		IOpenGL3Context * m_context;

	public:
		void Init(const g2::SharedPtr<IWindow>& window);

		Buffer* CreateBuffer(size_t initFlags);
	};
}