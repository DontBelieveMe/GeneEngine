#pragma once

#include <Platform/OpenGL.h>
#include <Graphics/Buffer.h>

#include <memory>
#include <vector>

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
		GLuint m_ID;
		std::vector<Buffer*> m_Buffers;

	public:
		VertexArray();
		~VertexArray();

		inline void Enable()  const { glBindVertexArray(m_ID); }
		inline void Disable() const { glBindVertexArray(0);    }

		void RegisterAttribute(Buffer *buffer, AttributeDescriptor attrib);

		void DebugDraw();
		void DebugDrawElements(Buffer *ebo);
	};
}}