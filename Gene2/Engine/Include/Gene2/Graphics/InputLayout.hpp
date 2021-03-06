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

		/**
		 * Represents a scalar float type for an attribute (GLSL: float)
		 */
		const static VertexAttribInputType Float;

		/**
		 * Represents a 2 component vector of floats (GLSL: vec2)
		 */
		const static VertexAttribInputType Float2;

		/**
		 * Represents a 3 component vector of floats (GLSL: vec3)
		 */
		const static VertexAttribInputType Float3;

		/**
		 * Represents a 4 component vector of float (GLSL: vec4)
		 */
		const static VertexAttribInputType Float4;
	};

	/**
	 * Stores data about a single vertex attribute input.
	 */
	class VertexAttribute
	{
	public:
		/**
		 * @brief Define the attributes of this vertex attribute.
		 * @param name The name of the attribute as appears in shader code
		 * @param index The index to bind the attribute to.
		 * @param type The equivalent type of the attribute. See VertexAttribInputType.
		 * @param streamIndex The index of the vertex stream that this attribute is attached to.
		 */
		void Define(const char* name, int index, const VertexAttribInputType& type, int streamIndex, int offset);

		/**
		 * @brief Get the index that this vertex attribute has been bound to.
		 * @return The index that this vertex attribute has been bound to.
		 */
		int GetIndex() const;

		/**
		 * @brief Get the ASCII string name of this attribute (as would appear in shader code).
		 * @return The name of this attribute.
		 */
		const char* GetName() const;

		int GetStreamIndex() const;

		int GetOffset() const;

		/**
		 * @brief Get the equivalent type of this attribute
		 * @return The type of this attribute.
		 */
		const VertexAttribInputType& GetType() const;

	private:
		int                   m_index;
		int                   m_streamIndex;
		VertexAttribInputType m_type;
		const char*           m_name;
		int                   m_offset;
	};

	class InputLayoutDef
	{
	public:
		const static int MAX_NUMBER_ATTRIBUTES = 10;

		InputLayoutDef& DefineAttribute(const char* name, int index, const VertexAttribInputType& type, int streamIndex, int offset);

		const Array<VertexAttribute>& GetAttributes() const;

	private:
		Array<VertexAttribute> m_attributes;
	};
}