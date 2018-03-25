// Copyright 2017-2018 Barney Wilks. All Rights Reserved

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
		void Resize(size_t newSize);

		template <typename T>
		T *GetPointer()
		{
			Enable();
			void *data = glMapBuffer(OpenGL::GeneToGLType(m_Type), GL_WRITE_ONLY);
			Disable();
			return reinterpret_cast<T*>(data);
		}
		
		void UnmapPointer();

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
