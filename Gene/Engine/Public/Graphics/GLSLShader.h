// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Core/String.h>
#include <Platform/OpenGL.h>
#include <string.h>
#include <Math/Math.h>

namespace gene { namespace graphics {
	class GLSLShader
	{
	private:
        GLuint       m_Program;
		mutable bool m_IsEnabled = false;

	public:
        void        CompileFromText    (const String& vert, const String& frag);
        void        CompileFromFiles   (const String& vertPath, const String& fragPath);
        void        BindAttributeIndex (GLint index, const char *name);

        GLuint GetProgram() { return m_Program; }

        inline void Enable()    const { glUseProgram(m_Program); m_IsEnabled = true;  }
        inline void Disable()   const { glUseProgram(0);         m_IsEnabled = false; }

		inline bool IsEnabled() const { return m_IsEnabled; }

		GLint       UniformLocation(const char *uniform);

		inline void LoadUniform3f(const char *uniform, const Vector3& vector) 
			            { glUniform3f(UniformLocation(uniform), vector.X, vector.Y, vector.Z); }

		inline void LoadUniform1f(const char* uniform, const float& v)
						{ glUniform1f(UniformLocation(uniform), v); }

		inline void LoadUniform2f(const char *uniform, const Vector2& vector)
			            { glUniform2f(UniformLocation(uniform), vector.X, vector.Y); }

		inline void LoadUniform4f(const char* uniform, const Vector4& vector)
						{ glUniform4f(UniformLocation(uniform), vector.X, vector.Y, vector.Z, vector.W); }

		inline void LoadUniformMatrix4f(const char *uniform, const Matrix4& mat)
                        { glUniformMatrix4fv(UniformLocation(uniform), 1, GL_TRUE, mat.Elements); }

        inline void LoadUniform1iv(const char *uniform, int * value, int count)
                         { glUniform1iv(UniformLocation(uniform), count, value); }

        inline void LoadUniformArrayElementi(const char *uniform, int value, int index)
        {
            GLint loc = UniformLocation(String(String(uniform, strlen(uniform)) + "[" + ToString(index) + "]").c_str());
            glUniform1i(loc, value);
        }
    };
}}
