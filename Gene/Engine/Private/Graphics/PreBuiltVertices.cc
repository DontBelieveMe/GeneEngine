#pragma once

#include <Graphics/PreBuiltVertices.h>

using namespace Gene::Graphics;

GLfloat PreBuiltVertices::RectangleVertices[]  = {
	0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f
};	

GLuint PreBuiltVertices::RectangleIndices[] = {
	0, 1, 3, 1, 2, 3
};

GLfloat PreBuiltVertices::CubeVertices[] = {
	-1.0, -1.0,  1.0, 1.0f, 0.0f,  0.0f,  1.0f, 1.0f,
	 1.0, -1.0,  1.0, 1.0f, 0.0f,  0.0f,  1.0f, 0.0f,
	-1.0,  1.0,  1.0, 0.0f, 0.0f,  1.0f,  0.0f, 0.0f,
	 1.0,  1.0,  1.0, 0.0f, 1.0f,  0.0f,  0.0f, 1.0f,
	-1.0, -1.0, -1.0, 1.0f, 0.0f,  0.0f,  1.0f, 1.0f,
	 1.0, -1.0, -1.0, 1.0f, 0.0f,  0.0f,  1.0f, 0.0f,
	-1.0,  1.0, -1.0, 0.0f, 1.0f,  0.0f,  0.0f, 0.0f,
	 1.0,  1.0, -1.0, 1.0f, 0.0f,  1.0f,  0.0f, 1.0f
};

GLuint PreBuiltVertices::CubeIndices[] = {
    0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
};
