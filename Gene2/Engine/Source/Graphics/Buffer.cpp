// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/Buffer.hpp>

using namespace g2;

void VertexBuffer::Create(size_t size, void* data) {
	G2_GL_CHECK(glGenBuffers(1, &m_id));
	// #todo (bwilks): Check buffer ID here (e.g it is non zero aka valid)

	G2_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	G2_GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
	G2_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}