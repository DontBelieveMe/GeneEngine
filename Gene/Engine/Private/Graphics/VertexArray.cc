// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Graphics/VertexArray.h>
#include <Graphics/Buffer.h>

#include <GeneCommon.h>

using namespace gene::graphics;

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
}

void VertexArray::RegisterAttribute(Buffer *buffer, AttributeDescriptor attrib)
{
    GE_ASSERT(attrib.Index >= 0, "Trying to register OpenGL VAO attribute with an index less than 0");
    GE_ASSERT(attrib.ComponentCount > 0, "Trying to register OpenGL VAO attribute with 0 or less components");

	Enable();
	buffer->Enable();

	glEnableVertexAttribArray(attrib.Index);
	
	glVertexAttribPointer(
		attrib.Index, 
		attrib.ComponentCount, 
		static_cast<GLenum>(buffer->DataType()),
		GL_FALSE, attrib.Stride, 
        (void*)(intptr_t)attrib.ByteOfffset
	);
	
	buffer->Disable();
	Disable();
}

void VertexArray::DrawElements(Buffer *ebo, int count)
{
    int _count = count < 0 ? ebo->Size() / sizeof(GLuint) : count;
    GE_ASSERT(_count >= 0, "VertexArray::DrawElements(...) element count is less than or equal to zero");

    Enable();
    ebo->Enable();
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, NULL);
    ebo->Disable();
    Disable();
}

void VertexArray::DrawArrays(int first, int count)
{
	glDrawArrays(GL_TRIANGLES, first, count);
}
