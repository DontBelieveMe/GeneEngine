// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/InputLayout.hpp>
#include <Gene2/Debug/Assert.hpp>

using namespace g2;

void VertexAttribute::Define(const char* name, int index, const VertexAttribInputType& type, int streamIndex, int offset)
{
	m_name = name;
	m_index = index;
	m_type = type;
	m_streamIndex = streamIndex;
	m_offset = offset;
}

int VertexAttribute::GetOffset() const
{
	return m_offset;
}

int VertexAttribute::GetIndex() const 
{
	return m_index;
}

const char* VertexAttribute::GetName() const 
{
	return m_name;
}

const VertexAttribInputType& VertexAttribute::GetType() const
{
	return m_type;
}

int VertexAttribute::GetStreamIndex() const
{
	return m_streamIndex;
}

InputLayoutDef& InputLayoutDef::DefineAttribute(const char* name, int index, const VertexAttribInputType& type, int streamIndex, int offset)
{
//	int offset = 0;

	VertexAttribute attrib;
	attrib.Define(name, index, type, streamIndex, offset);
	m_attributes.push_back(attrib);

	return *this;
}

const Array<VertexAttribute>& InputLayoutDef::GetAttributes() const
{
	return m_attributes;
}

const VertexAttribInputType VertexAttribInputType::Float(1, GLT_FLOAT);
const VertexAttribInputType VertexAttribInputType::Float2(2, GLT_FLOAT);
const VertexAttribInputType VertexAttribInputType::Float3(3, GLT_FLOAT);
const VertexAttribInputType VertexAttribInputType::Float4(4, GLT_FLOAT);

VertexAttribInputType::VertexAttribInputType(int nComponents, EOpenGLType type)
{
	NumComponents = nComponents;
	Type = type;
	switch (type)
	{
	case GLT_FLOAT:
		Size = NumComponents * sizeof(float);
		break;
	default:
		G2_ASSERT(false, "Unsupported vertex attribute data type");
	}
}