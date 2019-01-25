// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Graphics/OpenGL.hpp>

namespace g2 {
	enum EBufferFlags {
		BF_VERTEX_BUFFER = 1,
		BF_INDEX_BUFFER = 2
	};

	class Buffer {
	private:
		GLuint m_id;
		GLenum m_target;

	public:
		/**
		 * @brief Create an empty buffer.
		 * @param initFlags Flags used to configure the buffer. At a minimum must include BufferFlags (to set the type of buffer)
		 */
		void Create(size_t initFlags);

		/**
		 * @brief Get a read/write pointer to this buffers data store.
		 * @return A read/write pointer to this buffers data store.
		 */
		void* Map();

		/**
		 * @brief Unmap the pointer mapped with `Map()`. Must be called before this GL buffer is used.
		 */
		void Unmap();

		/**
		 * @brief Get the internal OpenGL buffer ID for this Buffer.
		 * @return OpenGL buffer object for this Buffer.
		 */
		GLuint GetId() const;
	};
}
