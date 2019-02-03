// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Platform/IWindow.hpp>

#include "IOpenGL3Context.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Color.hpp"
#include "OpenGL.hpp"
#include "MemoryRef.hpp"
#include "InputLayout.hpp"

#include "GraphicsResourceAllocator.hpp"

#include <Gene2/Core/StdLib/Array.hpp>

namespace g2 {
	enum EClearFlags {
		CF_CLEAR_DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT,
		CF_CLEAR_COLOR_BUFFER = GL_COLOR_BUFFER_BIT
	};

	enum EContextAttribute {
		CA_GL_MAJOR_VERSION,
		CA_GL_MINOR_VERSION,
		CA_GL_PROFILE
	};

	typedef GraphicsResourceHandle BufferHandle;
	typedef GraphicsResourceHandle ShaderHandle;
	
	/**
	 * Used to create resources and manage the rendering functionality of a window.
	 */
	class RenderDevice {
	public:
		static const size_t                         MaxVertexBuffers = 4096;
		static const size_t                         MaxShaders = 4096;

	private:
		IOpenGL3Context                            *m_context;

		Buffer                                      m_vertexBuffers[MaxVertexBuffers];
		GraphicsResourceAllocator<MaxVertexBuffers> m_vertexBufferHandles;

		Shader                                      m_shaders[MaxShaders];
		GraphicsResourceAllocator<MaxShaders>       m_shaderHandles;

		GLuint                                      m_gVao;
		ContextAttributes                           m_ctxAttribs;
	
	private:
		Buffer* GetBufferPtr(BufferHandle handle);
		Shader* GetShaderPtr(ShaderHandle handle);

	public:
		/**
		 * @brief Set an attribute to use when creating the OpenGL context. Must be called before Init().
		 *        Will assert if an invalid attribute is provided.
		 * @details The valid options for attribute and value are listed below
		 * <table>
		 *	<tr><th>Attribute             <th>Valid Values
		 *	<tr><td>::CA_GL_MAJOR_VERSION <td>Any valid OpenGL major version
		 *	<tr><td>::CA_GL_MINOR_VERSION <td>Any valid OpenGL minor version
		 *	<tr><td>::CA_GL_PROFILE       <td>Must be the value of one of ::EOpenGLProfile
		 * </table>
		 * @param attribute The attribute to set the value of.
		 * @param value The value to set the attribute to.
		 */
		void SetContextAttribute(EContextAttribute attribute, int value);

		/**
		 * @brief Initialize the RenderDevice for the specified IWindow
		 * @param window The window to initialize this graphics context for.
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
		 * @param flags What should be cleared - must be one of (or a "bitwise or" of multiple) ::EClearFlags
		 *              e.g Clear(CF_CLEAR_DEPTH_BUFFER) or Clear(CF_CLEAR_DEPTH_BUFFER | CF_CLEAR_COLOR_BUFFER)
		 */
		void Clear(u32 flags);

		/**
		 * @brief Swap the front and back buffers of this context.
		 */
		void SwapBuffers();

		/**
		 * @brief Create a new graphics buffer, with the specified initialization flags.
		 * @param initFlags Initialization flags to pass to the buffer on creation. see Buffer::Create(size_t)
		 * @param mem The data that will buffer will represent.
		 * @return A pointer to a new video Buffer. Do not free this buffer - it is owned by the graphics system.
		 */
		BufferHandle CreateBuffer(size_t initFlags, MemoryRef mem);

		/**
		 * @brief Create a new GLSL shader from the file at the specified filepath.
		 * @param filepath The path to the shader file.
		 * @param layoutDef The InputLayoutDef definition file for the input attributes of this shader pipeline.
		 * @return A pointer to a new video Shader. Do not free this shader - it is owned by the graphics system.
		 */
		ShaderHandle CreateShader(const char* filepath, InputLayoutDef layoutDef);

		/**
		 * @brief Issue a draw call to draw the specified number of primitives from the specified buffer, using the
		 *        specified shader.
		 * @param shader The shader to use when drawing this buffer.
		 * @param buffer The buffer to draw the primitives from.
		 * @param numPrimitives The number of primitives inside the buffer, for example the number of triangles to draw.
		 */
		void DrawPrimitive(ShaderHandle shader, BufferHandle buffer, size_t numPrimitives);
	};
}