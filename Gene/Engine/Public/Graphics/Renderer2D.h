// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Matrix4.h>

#include <Graphics/Font.h>
#include <Graphics/Color.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Buffer.h>
#include <Graphics/GLSLShader.h>
#include <Graphics/Texture2D.h>

#include <Core/String.h>
#include <Core/Array.h>

namespace Gene { namespace Graphics {
    
    /** Represents one vertex */
	struct Vertex2D 
	{
        Vector3     Position;
        Vector3     Color;
        Vector2     UV;
        float       TextureId;
	};

    /** Used for rendering data to the current framebuffer (which if none is specified the window). */
    class Renderer2D
    {
	private:
        VertexArray             *m_VAO;
        Buffer                  *m_VBO;
        Buffer                  *m_EBO;
        int                      m_IndexCount;

        Vertex2D                *m_Buffer;
        GLSLShader              *m_Shader;
        Matrix4                  m_ProjectionMatrix;
        Texture2D               *m_Texture;
        Array<Texture2D*>		 m_Textures;
		Array<Matrix4>			 m_TransformationStack;

    private:
        float GetTextureSlot(Texture2D *texture);

	public:
        /**
         * Default initalizes some values, but no actual renderer initalization is done here.
         * To propertly initalize the object call the Init() function
         */
		Renderer2D();

        /**
        * Draw a string the current buffer with the specified font at the specified window position
        * and with the specified colour.
        */
        void DrawString(Font *font,
            const String& text,
            const Vector2& pos,
            const Graphics::Color color
		);

        /** Draw the specified texture to the buffer at the specified window coordinates. */
		void DrawTexture(Vector2 position, Texture2D *texture);

        /** Draw a filled rectangle at the specified screen coordinates with the color, width and height specified. */
		void FillRectangle(Vector2 position, float width, float height, const Color& color);

        /** Initalise the renderer and set the projection matrix to be applied to the shapes rendered. */
        void Init(const Matrix4& projectionMatrix);

        /** Destroys any resources used by the renderer. Should be called instead of relying on destructor. */
		void Destroy();

        /** Unlocks the buffer for rendering. All drawing functions should come between a Begin() and End() call. */
		void Begin();

        /** Locks the buffers for writing and no drawing functions should be called again unless it is after a Begin() */
		void End();
		
        /** Draw the internal buffer to the current framebuffer. If no framebuffer is specified then it is drawn to the window. */
		void Present();

		void PushTransform(const Matrix4& matrix);

		void PopTransform();
    };
}}
