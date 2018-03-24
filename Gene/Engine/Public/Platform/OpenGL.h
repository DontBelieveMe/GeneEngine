// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#pragma once

#include "../../../ThirdParty/glfl/pregenerated/GLFL/glfl.h"

namespace Gene { namespace OpenGL {

    /** Utility enumeration that abstracts away OpenGL type definitions such as GL_FLOAT, GL_UNSIGNED_BYTE etc... */
	enum class GLType {
		Float			= GL_FLOAT,
		Int				= GL_INT,
		Byte		    = GL_BYTE,
		UnsignedByte    = GL_UNSIGNED_BYTE,
		Short		    = GL_SHORT,
		UnsignedInt     = GL_UNSIGNED_INT
    };

    /** Casts data of type "CustomType" to a GLenum. */
	template <typename CustomType>
	GLenum GeneToGLType(CustomType t)
	{
		return static_cast<GLenum>(t);
	}
}}
