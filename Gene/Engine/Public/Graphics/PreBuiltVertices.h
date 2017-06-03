#pragma once

#include <Platform/OpenGL.h>

namespace Gene { namespace Graphics {
	struct PreBuiltVertices {
		static  GLfloat RectangleVertices[32];
		static  GLuint  RectangleIndices[6];

		static  GLfloat CubeVertices[64];
		static  GLuint CubeIndices[14];
	};
}}