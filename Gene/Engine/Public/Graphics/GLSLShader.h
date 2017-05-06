#pragma once

#include <string>
#include <Platform/OpenGL.h>

#include <Math/Vector3.h>

namespace Gene { namespace Graphics {
	class GLSLShader
	{
	private:
		GLuint m_Program;

	public:
		void CompileFromText(const std::string& vert, const std::string& frag);
		void CompileFromFiles(std::string vertPath, std::string fragPath);

		inline void Enable() const { glUseProgram(m_Program); }
		inline void Disable() const { glUseProgram(0); }

		GLint UniformLocation(const char *uniform);

		inline void LoadUniform3f(const char *uniform, const Math::Vector3& vector) 
			{ glUniform3f(UniformLocation(uniform), vector.X, vector.Y, vector.Z); }
	};
}}