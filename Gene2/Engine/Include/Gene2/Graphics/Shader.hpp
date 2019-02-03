// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include "OpenGL.hpp"
#include "InputLayout.hpp"

namespace g2 {
	/**
	 * Represents a OpenGL shader program, created from a .shader file.
	 *
	 * The .shader file format is used to store the shader - .shader is just plain GLSL but with
	 * some special preprocessor commands (preprocessor commands should start with "#" and be separated on their own lines, like in C/C++).
	 *
	 * .shader files are separated into shader segments - each segment defines the GLSL for each separate part of the shader pipeline, for example 
	 * (at a minimum) .shader files must contain pixel and vertex segments, see below for specific 
	 *
	 * Special preprocessor commands:
	 *	- "#segment" - Used to start a new shader segment.
	 *    - Arguments:
	 *        - pixel -> This represents the start of the pixel shader code..
	 *        - vertex -> This represents the start of vertex shader code.
	 *    - Example Usage:
	 *        - "#segment pixel" -> Any following code is now pixel shader code until either the next "#segment" command or the end of the file.
	 *        - "#segment vertex" -> Any following code is vertex shader code until either the next "#segment" command or the end of the file.
	 */
	class Shader {
	public:
		/**
		 * @brief Create a shader from file.
		 * @param shaderFilename The filepath of the .shader file - must be a valid .shader file (see Shader).
		 * @param inputLayout The attributes layout of the shader pipeline.
		 */
		void Create(const char* shaderFilename, InputLayoutDef inputLayout);
		
		/**
		 * @brief Get the OpenGL object ID for this shader program.
		 * @return The OpenGL object ID for this shader program.
		 */
		GLuint GetProgramId() const;

		/**
		 * @brief Get the attributes input layout definition for this shader pipeline.
		 * @return The attributes input layout for this shader program.
		 */
		const InputLayoutDef& GetInputLayout() const;

	private:
		GLuint         m_programId;
		InputLayoutDef m_inputLayout;
	};
}