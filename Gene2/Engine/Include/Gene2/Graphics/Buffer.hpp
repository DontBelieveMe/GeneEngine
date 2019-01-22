// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Graphics/OpenGL.hpp>

namespace g2 {
	class VertexBuffer {
	public:
		void Create(size_t size, void* data);

	private:
		GLuint m_id;
	};

	class IndexBuffer {
	};
}