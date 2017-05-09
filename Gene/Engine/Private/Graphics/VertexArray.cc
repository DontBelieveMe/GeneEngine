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
	Enable();
	glVertexAttribPointer(
		attrib.Index, attrib.ComponentCount, static_cast<GLenum>(buffer->DataType()),
		GL_FALSE, attrib.Stride, (GLvoid*)attrib.ByteOfffset);
	glEnableVertexAttribArray(attrib.Index);
	//m_Buffers.push_back(buffer);
	Disable();
}

void VertexArray::DebugDraw()
{
	Enable();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	Disable();
}

void VertexArray::DebugDrawElements(Buffer *ebo)
{
	Enable();
	ebo->Enable();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	Disable();
	ebo->Disable();
}