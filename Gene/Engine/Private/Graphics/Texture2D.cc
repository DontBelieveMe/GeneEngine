#include <Graphics/Texture2D.h>

#include "External/lodepng.h"

using namespace Gene::Graphics;
using namespace Gene::Math;
using namespace Gene;

Texture2D::Texture2D(const char *filepath, int32 index)
{
	Load(filepath, index);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_TextureId);
}

void Texture2D::Load(const char *filepath, int32 index)
{
	GE_ASSERT(index < GL_MAX_TEXTURE_UNITS);
	GE_ASSERT(index >= 0);
	
	unsigned int error = lodepng::decode(m_Pixels, m_Width, m_Height, filepath);
	m_Loaded = !error;
	m_Index = index;

	if (m_Loaded)
	{
		GenerateGLId();
	}
}

void Texture2D::Load(uint8 *data, unsigned width, unsigned height, int32 index)
{
	GE_ASSERT(index < GL_MAX_TEXTURE_UNITS);
	GE_ASSERT(index >= 0);

	m_Pixels = std::vector<uint8>(data, data + width * height);
	m_Width = width;
	m_Height = height;
	m_Index = index;

	GenerateGLId();
	m_Loaded = true;
}

void Texture2D::GenerateGLId()
{
	/*// This is safe, as GL_TEXTURE<index> = GL_TEXTURE0 + <index>
	// https://www.khronos.org/registry/OpenGL-Refpages/es1.1/xhtml/glActiveTexture.xml
	glActiveTexture(GL_TEXTURE0 + m_Index);*/

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

void Texture2D::Enable(int32 index)
{
	// This is safe, as GL_TEXTURE<index> = GL_TEXTURE0 + <index>
	// https://www.khronos.org/registry/OpenGL-Refpages/es1.1/xhtml/glActiveTexture.xml
	glBindTexture(GL_TEXTURE_2D, m_TextureId); 
	glActiveTexture(GL_TEXTURE0 + index);
}

void Texture2D::Disable(int32 index)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}