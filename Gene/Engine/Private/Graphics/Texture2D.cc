// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Graphics/Texture2D.h>
#include <Core/Array.h>

#include "../../ThirdParty/lodepng/lodepng.h"

using namespace gene::graphics;
using namespace gene;

Texture2D::Texture2D(const char *filepath)
{
    Load(filepath);
}

void Texture2D::Destroy()
{
    glDeleteTextures(1, &m_TextureId);
}

// TODO: Marking for removal -> redundant due to new resource res->Destroy methods().
Texture2D::~Texture2D()
{}

void Texture2D::Load(const char *filepath, TextureParameters params)
{
	this->Parameters = params;

    unsigned int error = lodepng::decode(m_Pixels, m_Width, m_Height, filepath);
    m_Loaded = !error;
    
    if (m_Loaded)
    {
        GenerateGLId();
    }
}

void Texture2D::Load(uint8 *data, unsigned width, unsigned height, unsigned depth)
{
    m_Pixels = Array<uint8>(data, data + (width * height * depth));
    m_Width  = width;
    m_Height = height;

    GenerateGLId();
    m_Loaded = true;
}

void Texture2D::Load(const Array<uint8>& data, unsigned w, unsigned h)
{
    m_Pixels = data;
    m_Width = w;
    m_Height = h;
    GenerateGLId();
    m_Loaded = true;
}

void Texture2D::GenerateGLId()
{
    GLsizei w = static_cast<GLsizei>(m_Width);
    GLsizei h = static_cast<GLsizei>(m_Height);

    GLint filtering   = static_cast<GLint>(Parameters.Filtering);
    GLenum pixelFormat = static_cast<GLenum>(Parameters.Format);

    glGenTextures(1, &m_TextureId);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    uint8 *pData = m_Pixels.data();
    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        static_cast<GLint>(pixelFormat),
        w, h,
        0, 
        pixelFormat, 
        GL_UNSIGNED_BYTE, 
        pData
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

Vector2 Texture2D::SubTextureUV(float x, float y, float width, float height)
{
    float uvx = x / m_Width;
    float uvy = y / m_Height;
    return Vector2(uvx, uvy);
}

void Texture2D::Enable(size_t index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void Texture2D::Disable(size_t index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, 0);
}
