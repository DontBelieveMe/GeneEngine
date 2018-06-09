// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Graphics/Buffer.h>

using namespace gene::graphics;

Buffer::Buffer(Buffer::Type type): m_Type(type)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(static_cast<GLenum>(type), m_ID);
}

void Buffer::SetData(const BufferDescriptor& data)
{
	Enable();
	m_Descriptor = data;
	glBufferData(
		opengl::GeneToGLType(m_Type), 
		data.Size, 
		data.Data, 
		static_cast<GLenum>(data.DrawType));
	Disable();
}

void Buffer::Resize(size_t newSize)
{
	m_Descriptor.Size = newSize;

	Enable();
	glBufferData(
		opengl::GeneToGLType(m_Type),
		newSize,
		NULL,
		static_cast<GLenum>(m_Descriptor.DrawType)
	);
	Disable();
}

void Buffer::UnmapPointer()
{
	Enable();
	glUnmapBuffer(gene::opengl::GeneToGLType(m_Type));
	Disable();
}