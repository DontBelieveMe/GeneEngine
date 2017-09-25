#pragma once

#include <Platform/OpenGL.h>

namespace Gene { namespace Graphics {
	enum class BufferDrawType
	{
        Static  = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW,
        Stream  = GL_STREAM_DRAW
	};


	struct BufferDescriptor
	{
        size_t         Size;
        void          *Data;
		BufferDrawType DrawType;
		OpenGL::GLType DataType;
	};

	class Buffer {
	public:
		enum class Type
		{
            ArrayBuffer   = GL_ARRAY_BUFFER,
			ElementBuffer = GL_ELEMENT_ARRAY_BUFFER
		};

		Buffer(Type type);
		~Buffer() {}

		void SetData(const BufferDescriptor& data);
		
		inline void			  Enable()		   const { glBindBuffer(static_cast<GLenum>(m_Type), m_ID); }
		inline void			  Disable()		   const { glBindBuffer(static_cast<GLenum>(m_Type), 0); }
		inline size_t		  Size()		   const { return m_Descriptor.Size; }
		inline OpenGL::GLType DataType()	   const { return m_Descriptor.DataType; }
	private:
        GLuint           m_ID;
        Type             m_Type;
		BufferDescriptor m_Descriptor;
	};
}}
