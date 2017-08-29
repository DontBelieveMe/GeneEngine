#include "Shaders.h"

using namespace Gene::Graphics;

void Shaders::CompileAll() {
	this->Standard = new GLSLShader();
	this->Standard->CompileFromFiles("Data/vertex.glsl", "Data/fragment.glsl");
}

Shaders::~Shaders() {
	delete this->Standard;
}