// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Graphics/VertexArray.h>
#include <Graphics/Buffer.h>

#include <GeneCommon.h>

using namespace Gene::Graphics;

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
}

void VertexArray::RegisterAttribute(Buffer *buffer, AttributeDescriptor attrib)
{
    GE_ASSERT(attrib.Index >= 0);
    GE_ASSERT(attrib.ComponentCount > 0);

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

void VertexArray::DebugDraw()
{
    printf("I'm sorry, DebugDraw() [On VertexArray] should not be used, please see descriptive comments\n");
    GE_ASSERT(false);

	Enable();
    // VRAW ALL DA FRYANGLES! (Seriously though, TODO: Fix the hell outa this shit
    glDrawArrays(GL_TRIANGLES, 0, 10000);

	Disable();
}

void VertexArray::DebugDrawElements(Buffer *ebo, int count)
{
    int _count = count < 0 ? ebo->Size() / sizeof(GLuint) : count;
    GE_ASSERT(_count >= 0);

    Enable();
    ebo->Enable();
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, NULL);
    ebo->Disable();
    Disable();
}
