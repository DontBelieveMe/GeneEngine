// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include "OpenGL.hpp"

namespace g2
{
	class Texture
	{
	public:
		void Create(const char* filepath);

		GLuint GetId() const;

	private:
		GLuint m_id;
		int m_width, m_height;
		int m_channels;
	};
}