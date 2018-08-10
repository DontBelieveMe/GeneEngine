// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Graphics/GLSLShader.h>
#include <IO/File.h>
#include <Debug/Logger.h>

#include <stdio.h>
#include <stdlib.h>

using namespace gene::graphics;
using namespace gene;

#define SHADER_LOG_BUFFER_SIZE (512)    // Bytes

static GLuint CompileShader(const char *src, GLenum type)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
	    GLchar log[SHADER_LOG_BUFFER_SIZE];
		glGetShaderInfoLog(shader, SHADER_LOG_BUFFER_SIZE, NULL, log);
		LOG(LogLevel::Error, "Shader Compilation Error: ", type == GL_VERTEX_SHADER ? "Vertex Shader, " : "Fragment Shader, ", log);
        //GE_ASSERT(false, "Asserting on shader compile error!");
	}
	return shader;
}

void GLSLShader::CompileFromText(const String& vert, const String& frag)
{
	GLuint vertexShader = CompileShader(vert.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(frag.c_str(), GL_FRAGMENT_SHADER);

	m_Program = glCreateProgram();
	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fragmentShader);
	glLinkProgram(m_Program);

    GLint linkedCorrectly = 0;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &linkedCorrectly);

    if (!linkedCorrectly)
    {
        GLchar log[SHADER_LOG_BUFFER_SIZE];
        glGetProgramInfoLog(m_Program, SHADER_LOG_BUFFER_SIZE, NULL, log);

        LOG(LogLevel::Error, "Shader Linking Error: ", log);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
  //      GE_ASSERT(false, "Asserting on shader linking error");
    }

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void GLSLShader::CompileFromFiles(const String& vertPath, const String& fragPath)
{
	using namespace gene::io;
	File vert(vertPath.c_str());
	File frag(fragPath.c_str());
    
	String v = vert.Contents();
    String f = frag.Contents();

	CompileFromText(v, f);
}

void GLSLShader::BindAttributeIndex(GLint index, const char *name) 
{
    glBindAttribLocation(m_Program, index, name);
}

GLint GLSLShader::UniformLocation(const char *uniform)
{
	GLint loc = glGetUniformLocation(m_Program, uniform);

	if (loc < 0)
	{
        LOG(LogLevel::Warning, "Cannot get location of uniform: ", uniform);
	}

	return loc;
}
