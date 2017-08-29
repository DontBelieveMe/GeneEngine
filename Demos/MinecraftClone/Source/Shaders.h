#pragma once

#include <Graphics/GLSLShader.h>

class Shaders {
public :
	Gene::Graphics::GLSLShader *Standard;

	void CompileAll();

	~Shaders();
};