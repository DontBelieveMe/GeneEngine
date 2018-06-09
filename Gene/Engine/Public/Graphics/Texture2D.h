// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Platform/OpenGL.h>
#include <Math/Vector2.h>
#include <Core/Array.h>
#include <GeneCommon.h>

#include <Runtime/Resources.h>

namespace gene { namespace graphics {
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
        // BGRA = GL_BGRA,
        Red = GL_RED,

        Default = GL_RGBA,
        LuminanceAlpha = GL_LUMINANCE_ALPHA
    };

    struct TextureParameters {
        FilteringOptions Filtering = FilteringOptions::Default;
        PixelFormat		 Format    = PixelFormat::Default;
    };

    /** Represents an OpenGL tetxure object as well as the texture data itself. */
	class Texture2D : public IResource
	{
	private:
		bool					   m_Loaded;
        Array<uint8>               m_Pixels;
		GLuint					   m_TextureId;
		unsigned int			   m_Width;
		unsigned int			   m_Height;
		
	private:
		void GenerateGLId();

	public:
		Texture2D(const char *filepath);
		Texture2D(): m_Loaded(false) {}
		~Texture2D();

		virtual void Destroy();

		void Load(const char *path, TextureParameters params = TextureParameters());
		void Load(uint8 *data, unsigned width, unsigned height, unsigned depth = 1);
        void Load(const Array<uint8>& data, unsigned w, unsigned h);

        inline GLuint       Id()       const { return m_TextureId; }
        inline unsigned int Width()    const { return m_Width; }
        inline unsigned int Height()   const { return m_Height; }
		inline bool         IsLoaded() const { return m_Loaded; }
        void				Enable(size_t index);
        void				Disable(size_t index);
        const uint8        *Data()     const { return &m_Pixels[0]; }

		Vector2 SubTextureUV(float x, float y, float width, float height);

        TextureParameters Parameters;
	};
}}
