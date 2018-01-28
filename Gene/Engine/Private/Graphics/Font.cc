#include "FreetypeGL.h"

#include <Graphics/Font.h>
#include <iostream>
#include <IO/File.h>

#include <Platform/OpenGL.h>

using namespace Gene::Graphics;
using namespace Gene;

const float Font::DEFAULT_SIZE = 11.f;

Font::Font(const char *fontFile, float size): m_Size(size)
{
	const size_t ATLAS_SIZE  = 512;
	const int	 ATLAS_DEPTH = 1;
	
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	m_Atlas = ftgl::texture_atlas_new(ATLAS_SIZE, ATLAS_SIZE, ATLAS_DEPTH);

	m_Font  = texture_font_new_from_file(m_Atlas, size, fontFile);
    m_Font->rendermode = ftgl::RENDER_SIGNED_DISTANCE_FIELD;
    // For now just hack it and load all the ASCII characters
    // TODO: Remove this and do glyph loading on the fly when drawing the string
    //       Hence only loading the characters we need
    for (char c = '!'; c <= '~'; ++c) {
        texture_font_load_glyph(m_Font, &c);
    }

	m_Texture = new Texture2D();

    
	// TODO: The texture options should be put into a `TextureParamaters` struct  
	m_Texture->Format    = Texture2D::PixelFormat::Red;
	m_Texture->Filtering = Texture2D::FilteringOptions::Linear;

	m_Texture->Load(m_Atlas->data, ATLAS_SIZE, ATLAS_SIZE);
}

Font::~Font() 
{
	delete m_Texture;

	texture_font_delete(m_Font);
	texture_atlas_delete(m_Atlas);
}

Vector2 Font::MeasureString(const std::string & str)
{
    float width = 0.0f;
    float height = 0.0f;

    for (char character : str) {
        ftgl::texture_glyph_t *glyph = ftgl::texture_font_get_glyph(m_Font, &character);
        width += glyph->advance_x;
        if (glyph->advance_y > height) {
            height = glyph->advance_y;
        }
    }

    return Vector2(width, height);
}
