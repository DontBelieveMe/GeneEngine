#include "FreetypeGL.h"

#include <Graphics/Font.h>
#include <iostream>
#include <IO/File.h>

using namespace Gene::Graphics;

const float Font::DEFAULT_SIZE = 11.f;

Font::Font(const char *fontFile, float size): m_Size(size)
{
	const size_t ATLAS_SIZE  = 512;
	const int	 ATLAS_DEPTH = 4;
	
	m_Atlas = texture_atlas_new(ATLAS_SIZE, ATLAS_SIZE, ATLAS_DEPTH);
	m_Font  = texture_font_new_from_file(m_Atlas, size, fontFile);
	
	m_Texture = new Texture2D();

	// TODO: The texture options should be put into a `TextureParamaters` struct  
	m_Texture->Format    = Texture2D::PixelFormat::Red;
	m_Texture->Filtering = Texture2D::FilteringOptions::Linear;

	m_Texture->Load(m_Atlas->data, ATLAS_SIZE, ATLAS_SIZE, 0);
}

Font::~Font() 
{
	delete m_Texture;

	texture_font_delete(m_Font);
	texture_atlas_delete(m_Atlas);
}
