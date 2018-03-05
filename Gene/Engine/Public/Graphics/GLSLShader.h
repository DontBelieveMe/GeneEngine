#pragma once

#include <string>
#include <Platform/OpenGL.h>

#include <Math/Math.h>

namespace Gene { namespace Graphics {
	class GLSLShader
	{
	private:
        GLuint       m_Program;
		mutable bool m_IsEnabled = false;

	public:
        void        CompileFromText    (const std::string& vert, const std::string& frag);
        void        CompileFromFiles   (std::string vertPath, std::string fragPath);
        void        BindAttributeIndex (GLint index, const char *name);

        inline void Enable()    const { glUseProgram(m_Program); m_IsEnabled = true;  }
        inline void Disable()   const { glUseProgram(0);         m_IsEnabled = false; }

		inline bool IsEnabled() const { return m_IsEnabled; }

		GLint       UniformLocation(const char *uniform);

		inline void LoadUniform3f(const char *uniform, const Vector3& vector) 
			            { glUniform3f(UniformLocation(uniform), vector.X, vector.Y, vector.Z); }

		inline void LoadUniform2f(const char *uniform, const Vector2& vector)
			            { glUniform2f(UniformLocation(uniform), vector.X, vector.Y); }

		inline void LoadUniformMatrix4f(const char *uniform, const Matrix4& mat)
                        { glUniformMatrix4fv(UniformLocation(uniform), 1, GL_TRUE, mat.Elements); }

        inline void LoadUniform1iv(const char *uniform, int * value, int count)
                         { glUniform1iv(UniformLocation(uniform), count, value); }
    };
}}
