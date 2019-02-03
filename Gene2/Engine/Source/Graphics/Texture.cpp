// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/Texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <Gene2/Lib/stb_image.Lib.hpp>

#include <Gene2/Debug/Assert.hpp>

using namespace g2;

void Texture::Create(const char* filepath)
{
	stbi_uc* data = stbi_load(filepath, &m_width, &m_height, &m_channels, STBI_rgb_alpha);
	
	G2_ASSERT(data, "Could not load texture {0}", filepath);

	// #todo(bwilks): #cleanup #improvment
	// Support more texture types than just 2D.
	const GLenum kTargetType = GL_TEXTURE_2D;

	G2_GL_CHECK(glGenTextures(1, &m_id));
	G2_GL_CHECK(glBindTexture(kTargetType, m_id));
	
	// #todo(bwilks): #cleanup #api
	// Texture parameters should be exposed to the user instead of them being hard coded.
	G2_GL_CHECK(glTexParameteri(kTargetType, GL_TEXTURE_WRAP_S, GL_REPEAT));
	G2_GL_CHECK(glTexParameteri(kTargetType, GL_TEXTURE_WRAP_T, GL_REPEAT));

	G2_GL_CHECK(glTexParameteri(kTargetType, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	G2_GL_CHECK(glTexParameteri(kTargetType, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	G2_GL_CHECK(glTexImage2D(kTargetType, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	G2_GL_CHECK(glGenerateMipmap(kTargetType));

	G2_GL_CHECK(glBindTexture(kTargetType, 0));

	stbi_image_free(data);
}

GLuint Texture::GetId() const
{
	return m_id;
}