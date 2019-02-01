// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include "OpenGL.hpp"
#include "GraphicsResourceAllocator.hpp"

#include <Gene2/Core/StdLib/Array.hpp>

namespace g2
{
	struct VertexAttribInputType
	{
		/**
		 * The number of components in the type. Must be 1, 2, 3 or 4
		 */
		int NumComponents;

		/**
		 * The fundamental type that this vertex attribute is made up of.
		 */
		EOpenGLType Type;

		/**
		 * The size in bytes of the vertex attribute
		 */
		int Size;

		VertexAttribInputType(int nComponents, EOpenGLType type);

		VertexAttribInputType(){}

		const static VertexAttribInputType Float;
		const static VertexAttribInputType Float2;
		const static VertexAttribInputType Float3;
		const static VertexAttribInputType Float4;
	};

	class VertexAttribute
	{
	public:
		void Define(const char* name, int index, const VertexAttribInputType& type);

		int GetIndex() const;
		const char* GetName() const;
		const VertexAttribInputType& GetType() const;

	private:
		int m_index;
		VertexAttribInputType m_type;
		const char* m_name;
	};

	class InputLayoutDef
	{
	public:
		const static int MAX_NUMBER_ATTRIBUTES = 10;

		void DefineAttribute(const char* name, int index, const VertexAttribInputType& type);

		const Array<VertexAttribute>& GetAttributes() const;

	private:
		Array<VertexAttribute> m_attributes;
	};

	class BufferArray
	{
	public:
		void Create();
		GLuint GetId() const;

		void AddBuffer(GraphicsResourceHandle buff);

		const Array<GraphicsResourceHandle>& GetBuffers() const;

	private:
		GLuint m_id;
		Array<GraphicsResourceHandle> m_buffers;
	};
}