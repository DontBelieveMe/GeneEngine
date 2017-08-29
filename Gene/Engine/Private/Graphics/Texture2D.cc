#include <Graphics/Texture2D.h>

#include "External/lodepng.h"

using namespace Gene::Graphics;
using namespace Gene::Math;

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

void Texture2D::Load(unsigned char *data, unsigned width, unsigned height)
{
	m_Pixels = std::vector<unsigned char>(data, data + width * height);
	m_Width = width;
	m_Height = height;

	GenerateGLId();
	m_Loaded = true;
}

void Texture2D::GenerateGLId()
{
	glActiveTexture(GL_TEXTURE0);
	GLenum filtering = static_cast<GLenum>(Filtering);

	glGenTextures(1, &m_TextureId);
	Enable();
	glBindTexture(GL_TEXTURE_2D, m_TextureId); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_Pixels[0]);
	Disable();
}

Vector2 Texture2D::SubTextureUV(float x, float y, float width, float height)
{
	float uvx = x / m_Width;
	float uvy = y / m_Height;
	return Vector2(uvx, uvy);
}