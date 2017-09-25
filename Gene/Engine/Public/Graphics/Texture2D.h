#pragma once
#pragma once

#include <vector>

#include <Platform/OpenGL.h>
#include <Math/Vector2.h>
#include <GeneCommon.h>

namespace Gene { namespace Graphics {
	class Texture2D
	{
	private:
		bool					   m_Loaded;
		std::vector<uint8> m_Pixels;
		GLuint					   m_TextureId;
		unsigned int			   m_Width;
		unsigned int			   m_Height;
	
	private:
		void GenerateGLId();

	public:
		Texture2D(const char *filepath);
		Texture2D(): m_Loaded(false) {}

		void Load(const char *path);
		void Load(uint8 *data, unsigned width, unsigned height);

        inline GLuint       Id()       const { return m_TextureId; }
        inline unsigned int Width()    const { return m_Width; }
        inline unsigned int Height()   const { return m_Height; }
		inline bool         IsLoaded() const { return m_Loaded; }
        inline void			Enable()   const { glBindTexture(GL_TEXTURE_2D, m_TextureId); }
        inline void			Disable()  const { glBindTexture(GL_TEXTURE_2D, 0); }
        int8               *Data()     const { return &m_Pixels[0]; }

		Math::Vector2 SubTextureUV(float x, float y, float width, float height);

		enum class FilteringOptions
		{
			Linear  = GL_LINEAR, 
			Nearest = GL_NEAREST,
			Default = GL_LINEAR
		};

		enum class PixelFormat
		{
			RGBA = GL_RGBA,
			RGB = GL_RGBA,
			BGRA = GL_BGRA,
			Red = GL_RED,

			Default = GL_RGBA
		};

		FilteringOptions Filtering = FilteringOptions::Default;
		PixelFormat		 Format    = PixelFormat::Default;
	};
}}
