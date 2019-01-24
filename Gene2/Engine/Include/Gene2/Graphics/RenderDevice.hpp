// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Graphics/IOpenGL3Context.hpp>
#include <Gene2/Platform/IWindow.hpp>
#include <Gene2/Graphics/Buffer.hpp>

namespace g2 {
	/**
	 * Used to create resources and manage the rendering functionality of a window.
	 */
	class RenderDevice {
	private:
		IOpenGL3Context * m_context;

	public:
		/**
		 * @brief Initialize the RenderDevice for the specified IWindow
		 */
		void Init(const g2::SharedPtr<IWindow>& window);

		/**
		 * @brief Create a new graphics buffer, with the specified initialization flags.
		 * @param initFlags Initialization flags to pass to the buffer on creation. see Buffer::Create(size_t)
		 * @return A pointer to a new video Buffer. Do not free this buffer - it is owned by the graphics system.
		 */
		Buffer* CreateBuffer(size_t initFlags);
	};
}