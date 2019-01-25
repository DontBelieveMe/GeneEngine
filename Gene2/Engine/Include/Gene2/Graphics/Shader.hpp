// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include "OpenGL.hpp"

namespace g2 {
	class Shader {
	public:
		void Create(const char* shaderFilename);
		
		GLuint GetProgramId() const;

	private:
		GLuint m_programId;
	};
}