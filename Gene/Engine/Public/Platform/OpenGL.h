// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once
#include <Platform/OS.h>
#include <Core/String.h>

#if defined(GENE_OS_ANDROID)
	#include <EGL/egl.h>
	#include <GLES3/gl32.h>
	#include <GLES3/gl3ext.h>
#else
	#include "../../../ThirdParty/glfl/pregenerated/GLFL/glfl.h"
#endif

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

#if defined(GENE_OS_ANDROID)
	// https://stackoverflow.com/questions/38127022/is-there-a-standard-way-to-query-egl-error-string
	#define CASE_STR( value ) case value: return #value; 
	inline String GetErrorString( EGLint error )
	{
	    switch( error )
	    {
	    CASE_STR( EGL_SUCCESS             )
	    CASE_STR( EGL_NOT_INITIALIZED     )
	    CASE_STR( EGL_BAD_ACCESS          )
	    CASE_STR( EGL_BAD_ALLOC           )
	    CASE_STR( EGL_BAD_ATTRIBUTE       )
	    CASE_STR( EGL_BAD_CONTEXT         )
	    CASE_STR( EGL_BAD_CONFIG          )
	    CASE_STR( EGL_BAD_CURRENT_SURFACE )
	    CASE_STR( EGL_BAD_DISPLAY         )
	    CASE_STR( EGL_BAD_SURFACE         )
	    CASE_STR( EGL_BAD_MATCH           )
	    CASE_STR( EGL_BAD_PARAMETER       )
	    CASE_STR( EGL_BAD_NATIVE_PIXMAP   )
	    CASE_STR( EGL_BAD_NATIVE_WINDOW   )
	    CASE_STR( EGL_CONTEXT_LOST        )
	    default: return "Unknown";
	    }
	}
	#undef CASE_STR
#endif
}}
