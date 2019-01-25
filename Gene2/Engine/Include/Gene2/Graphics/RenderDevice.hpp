// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Platform/IWindow.hpp>

#include "IOpenGL3Context.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Color.hpp"
#include "OpenGL.hpp"

#include <Gene2/Core/StdLib/Array.hpp>

namespace g2 {
	enum EClearFlags {
		CF_CLEAR_DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT,
		CF_CLEAR_COLOR_BUFFER = GL_COLOR_BUFFER_BIT
	};

	/**
	 * Used to create resources and manage the rendering functionality of a window.
	 */
	class RenderDevice {
	private:
		IOpenGL3Context * m_context;

		Array<Buffer> m_buffers;
	public:
		/**
		 * @brief Initialize the RenderDevice for the specified IWindow
		 */
		void Init(const g2::SharedPtr<IWindow>& window);

		/**
		 * @brief Set the clear color of this device. The active framebuffer will be reset to this color when
		 *        Clear() is called.
		 * @param color The new clear color of this RenderDevice.
		 */
		void SetClearColor(const Color& color);

		/**
		 * @brief Clear the current framebuffer to the last color set by SetClearColor or black if
		 *        SetClearColor has not been called.
		 */
		void Clear(u32 flags);

		void SwapBuffers();

		/**
		 * @brief Create a new graphics buffer, with the specified initialization flags.
		 * @param initFlags Initialization flags to pass to the buffer on creation. see Buffer::Create(size_t)
		 * @return A pointer to a new video Buffer. Do not free this buffer - it is owned by the graphics system.
		 */
		Buffer* CreateBuffer(size_t initFlags);

		Shader* CreateShader(const char* filepath);
	};
}