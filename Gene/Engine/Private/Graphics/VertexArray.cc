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
	GLsizei stride = buffer->Size() / attrib.ComponentCount;
	glVertexAttribPointer(
		attrib.Index, attrib.ComponentCount, OpenGL::GeneToGLType(buffer->DataType()),
		GL_FALSE, stride, (GLvoid*)attrib.ByteOfffset);
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