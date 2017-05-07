#include <Graphics/Texture2D.h>

#include "External/lodepng.h"

using namespace Gene::Graphics;

Texture2D::Texture2D(const char *filepath)
{
	Load(filepath);
}

void Texture2D::Load(const char *filepath)
{
	unsigned int error = lodepng::decode(m_Pixels, m_Width, m_Height, filepath);
	m_Loaded = !error;
	
	if (m_Loaded)
	{
		GenerateGLId();
	}
}

void Texture2D::GenerateGLId()
{
	GLfloat filtering = static_cast<GLfloat>(Filtering);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_TextureId);
	Enable();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_Pixels[0]);
	Disable();
}