// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Lib/glfl.Lib.hpp>

#ifndef NDEBUG
#define G2_GL_CHECK(glCall) \
	glCall; \
	if(glGetError()) \
		G2_FATAL(#glCall ": GL eror {0}", glGetError());

#else
#define G2_GL_CHECK(glCall) glCall;
#endif

namespace g2
{
	enum EOpenGLType
	{
		GLT_FLOAT = GL_FLOAT
	};
}