// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/Buffer.hpp>
#include <Gene2/Debug/Assert.hpp>

using namespace g2;

void Buffer::Create(size_t initFlags)
{
	if (initFlags & BF_VERTEX_BUFFER)
		m_target = GL_ARRAY_BUFFER;
	else if (initFlags & BF_INDEX_BUFFER)
		m_target = GL_ELEMENT_ARRAY_BUFFER;
	else 
		G2_ASSERT(false, "Buffer type not specified.");

	G2_GL_CHECK(glGenBuffers(1, &m_id));
		
	G2_ASSERT(m_id != 0, "Could not generate GL buffer!");
}

void* Buffer::Map()
{
	void* ptr = G2_GL_CHECK(glMapBuffer(m_target, GL_READ_WRITE));
	
	G2_ASSERT(ptr, "Could not map GL buffer.");

	return ptr;
}

void Buffer::Unmap()
{
	G2_GL_CHECK(glUnmapBuffer(m_target));
}

GLuint Buffer::GetId() const {
	return m_id;
}
