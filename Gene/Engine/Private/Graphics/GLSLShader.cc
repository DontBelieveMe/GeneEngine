// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#include <Graphics/GLSLShader.h>
#include <IO/File.h>

#include <stdio.h>
#include <stdlib.h>

using namespace Gene::Graphics;
using namespace Gene;

static GLuint CompileShader(const char *src, GLenum type)
{
	const int SHADER_LOG_BUFFER_SIZE = 512;	// Bytes

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar log[SHADER_LOG_BUFFER_SIZE];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, SHADER_LOG_BUFFER_SIZE, NULL, log);
		printf("Shader Error: [%s] -> %s\n", type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader", log);
		abort();
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
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void GLSLShader::CompileFromFiles(const String& vertPath, const String& fragPath)
{
	using namespace Gene::IO;
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
		printf("Can not get uniform location: %s\n", uniform);
	}

	return loc;
}
