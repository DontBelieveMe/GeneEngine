#include <Graphics/Buffer.h>

using namespace Gene::Graphics;

Buffer::Buffer(Buffer::Type type): m_Type(type)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(static_cast<GLenum>(type), m_ID);
}

void Buffer::SetData(const BufferDescriptor& data)
{
	m_Descriptor = data;
	glBufferData(
		OpenGL::GeneToGLType(m_Type), 
		data.Size, 
		data.Data, 
		static_cast<GLenum>(data.DrawType));
}