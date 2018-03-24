// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#pragma once

#include <Platform/OpenGL.h>
#include <Graphics/Buffer.h>
#include <Core/Array.h>

#include <memory>

namespace Gene { namespace Graphics {
	struct AttributeDescriptor
	{
		int Index;
		int ComponentCount;
		int ByteOfffset;
		int Stride;
	};

	class VertexArray
	{
	private:
        GLuint               m_ID;
		Array<Buffer*> m_Buffers;

	public:
		VertexArray();
		~VertexArray();

		inline void Enable()  const { glBindVertexArray(m_ID); }
		inline void Disable() const { glBindVertexArray(0);    }

		void RegisterAttribute(Buffer *buffer, AttributeDescriptor attrib);

		void DebugDraw();
		void DebugDrawElements(Buffer *ebo, int count=-1);
	};
}}
