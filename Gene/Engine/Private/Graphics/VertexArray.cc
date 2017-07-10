#include <Graphics/VertexArray.h>
#include <Graphics/Buffer.h>

using namespace Gene::Graphics;

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
	for(Buffer* ptr : m_Buffers)
	{
		delete ptr;
		ptr = nullptr;
	}
}

void VertexArray::RegisterAttribute(Buffer *buffer, AttributeDescriptor attrib)
{
	buffer->Enable();
	Enable();
	glEnableVertexAttribArray(attrib.Index);
	glVertexAttribPointer(
		attrib.Index, attrib.ComponentCount, static_cast<GLenum>(buffer->DataType()),
		GL_FALSE, attrib.Stride, (GLvoid*)attrib.ByteOfffset);
	Disable();
	buffer->Disable();
}

void VertexArray::DebugDraw()
{
	Enable();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Disable();
}

void VertexArray::DebugDrawElements(Buffer *ebo)
{
	Enable();
	ebo->Enable();
    int size;  
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
	ebo->Disable();
	Disable();
}