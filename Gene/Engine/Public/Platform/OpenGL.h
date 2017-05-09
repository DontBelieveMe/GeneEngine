#pragma once

#include <GLFL/glfl.h>

namespace Gene { namespace OpenGL {

	enum class GLType {
		Float			= GL_FLOAT,
		Int				= GL_INT,
		Byte		    = GL_BYTE,
		UnsignedByte    = GL_UNSIGNED_BYTE,
		Short		    = GL_SHORT,
		UnsignedInt     = GL_UNSIGNED_INT
	};

	template <typename CustomType>
	GLenum GeneToGLType(CustomType t)
	{
		return static_cast<GLenum>(t);
	}
}}