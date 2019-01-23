// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Graphics/OpenGL.hpp>

namespace g2 {
	enum BufferFlags {
		BF_VERTEX_BUFFER,
		BF_INDEX_BUFFER
	};

	class Buffer {
	private:
		GLuint m_id;
		GLenum m_target;

	public:
		void Create(size_t initFlags);

		void* Map();
		void Unmap();

		GLuint GetId() const;
	};
}