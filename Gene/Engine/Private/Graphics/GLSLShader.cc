#include <Graphics/GLSLShader.h>
#include <IO/File.h>

#include <stdio.h>

using namespace Gene::Graphics;

static GLuint CompileShader(const char *src, GLenum type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, log);
		printf("Shader Error: [%s] -> %s\n", type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader", log);
		abort();
	}
	return shader;
}

void GLSLShader::CompileFromText(const std::string& vert, const std::string& frag)
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

void GLSLShader::CompileFromFiles(std::string vertPath, std::string fragPath)
{
	using namespace Gene::IO;

	File vert(vertPath.c_str());
	File frag(fragPath.c_str());

	CompileFromText(vert.Contents(), frag.Contents());
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