// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include "OpenGL.hpp"
#include "InputLayout.hpp"

namespace g2 {
	class Shader {
	public:
		void Create(const char* shaderFilename, InputLayoutDef inputLayout);
		
		GLuint GetProgramId() const;
		InputLayoutDef GetInputLayout() const;

	private:
		GLuint m_programId;
		InputLayoutDef m_inputLayout;
	};
}