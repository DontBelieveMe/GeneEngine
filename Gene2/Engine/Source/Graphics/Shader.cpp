// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/Shader.hpp>
#include <Gene2/Core/StdLib/File.hpp>
#include <Gene2/Debug/Assert.hpp>

#include <cctype>

using namespace g2;

enum EShaderSegment {
	SS_VERTEX = GL_VERTEX_SHADER,
	SS_PIXEL  = GL_FRAGMENT_SHADER,
	SS_NONE   = 0
};

struct ShaderSegment {
	String SourceString;           ///< The actual shader code that makes up this segment
	EShaderSegment Type = SS_NONE; ///< The type of this shader (vertex, fragment, etc...)
	GLuint OpenGLID;               ///< The OpenGL Id for this shader. Generated after preprocessing by OpenGL.
};

static Array<ShaderSegment> PreprocessShaderFile(const String& shaderText) {
	Array<ShaderSegment> shaders;

	size_t cindex = 0;
	while (cindex < shaderText.length() - 1) {
		if (shaderText[cindex] == '#') {
			cindex++; // skip past the '#'

			const size_t startidx = cindex;
			while (isalpha(shaderText[cindex])) {
				cindex++;
			}

			const String directive(shaderText.begin() + startidx, shaderText.begin() + cindex);
			
			if (directive == "section") {
				ShaderSegment segment;
				while (shaderText[cindex] == ' ' || shaderText[cindex] == '\t') cindex++;

				const size_t shaderTypeStarIdx = cindex;
				while (isalpha(shaderText[cindex])) {
					cindex++;
				}

				const String shaderType(shaderText.begin() + shaderTypeStarIdx, shaderText.begin() + cindex);

				if (shaderType == "vertex") segment.Type = SS_VERTEX;
				else if (shaderType == "pixel") segment.Type = SS_PIXEL;

				G2_ASSERT(segment.Type != SS_NONE, "Invalid shader type name!");

				shaders.push_back(segment);
			}
		}
		else {
			if (shaders.size() > 0) {
				ShaderSegment& segment = shaders.back();
				segment.SourceString += shaderText[cindex];
			}
		}

		++cindex;
	}

	G2_ASSERT(shaders.size() > 0, "No shader type specified.");

	return shaders;
}

static GLuint CreateShaderFromSegmentData(const ShaderSegment& segment)
{
	const char* txt = segment.SourceString.c_str();
	GLuint shaderId = glCreateShader(static_cast<GLenum>(segment.Type));

	glShaderSource(shaderId, 1, &txt, nullptr);
	glCompileShader(shaderId);

	GLint success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	
	const size_t MAX_GLSL_ERROR_LOG_SIZE = 512;

	if (!success)
	{
		GLchar log[MAX_GLSL_ERROR_LOG_SIZE];
		glGetShaderInfoLog(shaderId, MAX_GLSL_ERROR_LOG_SIZE, nullptr, log);
		
		const char* shaderTypeAsString = segment.Type == SS_PIXEL ? "Pixel shader" : segment.Type == SS_VERTEX ? "Vertex shader" : "<Unknown shader>";
	
		G2_ERROR("{0} compilation error:\n{1}", shaderTypeAsString, log);
	}

	return shaderId;
}

void Shader::Create(const char* shaderFilename)
{
	String fileText = File::ReadAllText(shaderFilename);
	Array<ShaderSegment> segments = PreprocessShaderFile(fileText);

	const GLuint program = glCreateProgram();

	for (ShaderSegment& shaderSegment : segments) {
		shaderSegment.OpenGLID = CreateShaderFromSegmentData(shaderSegment);
		glAttachShader(program, shaderSegment.OpenGLID);
	}

	glLinkProgram(program);

	// #todo(bwilks) add link error checking step here
	
	for (ShaderSegment& shaderSegment : segments) {
		glDeleteShader(shaderSegment.OpenGLID);
	}

	m_programId = program;
}

GLuint Shader::GetProgramId() const {
	return m_programId;
}