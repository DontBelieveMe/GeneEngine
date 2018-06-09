// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Platform/OpenGL.h>
#include <Debug/Logger.h>

namespace gene { namespace graphics {
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
		opengl::GLType DataType;
	};

	class Buffer {
	public:
		enum class Type
		{
            ArrayBuffer   = GL_ARRAY_BUFFER,
			ElementBuffer = GL_ELEMENT_ARRAY_BUFFER
		};

        /** Create a buffer with the specified buffer array type -> e.g Type::ArrayBuffer or Type::ElementBuffer */
		Buffer(Type type);

		~Buffer() {}

        /** Set the data of this array (data described by the specified BufferDescriptor)*/
		void SetData(const BufferDescriptor& data);

        /** Resize this buffer to have the specified new size (in bytes)*/
		void Resize(size_t newSize);

        /** Return a pointer to the memory used by this buffer. */
		template <typename T>
		T *GetPointer()
		{
			Enable();
            int x;
            glGetBufferParameteriv(opengl::GeneToGLType(m_Type), GL_BUFFER_SIZE, &x);

			void *data = glMapBufferRange(opengl::GeneToGLType(m_Type), 0, Size(), GL_MAP_WRITE_BIT);
            
            if (!data) {
                LOG(LogLevel::Infomation, "Buffer::GetPointer<T>() is returning a null pointer (Buffer ID: ", m_ID, ")");
            }

			Disable();
			return reinterpret_cast<T*>(data);
		}
		
        /** Unmap the pointer given by `GetPointer<T>()` so that it is no longer valid to be used in client code. */
		void UnmapPointer();

        /** Bind this buffer to the appropriate slot (specified by `Type` set by constructor) */
		inline void			  Enable()		   const { glBindBuffer(static_cast<GLenum>(m_Type), m_ID); }

        /** Set the currently bound buffer of this type to be 0. */
		inline void			  Disable()		   const { glBindBuffer(static_cast<GLenum>(m_Type), 0); }

        /** Return the total size of the data used by this buffer (in btyes).*/
		inline size_t		  Size()		   const { return m_Descriptor.Size; }

        /** Return the OpenGL data type of the data stored in this buffer. */
		inline opengl::GLType DataType()	   const { return m_Descriptor.DataType; }

	private:
        GLuint           m_ID;
        Type             m_Type;
		BufferDescriptor m_Descriptor;
	};
}}
