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

void Texture2D::Load(Gene::uint8 *data, unsigned width, unsigned height)
{
	m_Pixels = std::vector<Gene::uint8>(data, data + width * height);
	m_Width = width;
	m_Height = height;

	GenerateGLId();
	m_Loaded = true;
}

void Texture2D::GenerateGLId()
{
	glActiveTexture(GL_TEXTURE0);

	GLenum filtering   = static_cast<GLenum>(Filtering);
	GLenum pixelFormat = static_cast<GLenum>(Format);

	glGenTextures(1, &m_TextureId);

	Enable();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
	
	uint8 *pData = m_Pixels.data();
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		pixelFormat, 
		m_Width, m_Height, 
		0, 
		pixelFormat, 
		GL_UNSIGNED_BYTE, 
		pData
	);

	Disable();
}

Vector2 Texture2D::SubTextureUV(float x, float y, float width, float height)
{
	float uvx = x / m_Width;
	float uvy = y / m_Height;
	return Vector2(uvx, uvy);
}