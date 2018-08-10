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

namespace gene { namespace graphics {
    
    /** Represents one vertex */
	struct Vertex2D 
	{
        Vector3     Position;
        Vector3     Color;
        Vector2     UV;
        float       TextureId;
	};

    enum class TextAlignment
    {
        Left,
        Right,
        Centre
    };

    struct AABBRectangle
    {
        Vector2 TopLeft, TopRight, BottomLeft, BottomRight;

        AABBRectangle() {};
        AABBRectangle(Vector2 tl, Vector2 tr, Vector2 bl, Vector2 br) : TopLeft(tl), TopRight(tr), BottomLeft(bl), BottomRight(br) {}
    };

	struct Light {
		Vector3 Position;
		float Size;
		float Intensity;
		float Falloff;
		Color Colour;

		Light(const Vector3& pos, float size, float intensity, float falloff, const Color& col) :
			Position(pos), Size(size), Intensity(intensity), Falloff(falloff), Colour(col) {}

		Light() {}
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
        unsigned int            *m_Indices;
        GLSLShader              *m_Shader;
        Matrix4                  m_ProjectionMatrix;
        Array<Texture2D*>		 m_Textures;
		Array<Matrix4>			 m_TransformationStack;
        unsigned int             m_IndexOffset;
		Array<Light*>			 m_Lights;
    private:
        float GetTextureSlot(Texture2D *texture);

        void WriteRectangleIndices();

	public:
		GLSLShader * GetShader() { return m_Shader; }

		void LoadLights(Array<Light*>& lights);
		void LoadLight(Light *light, int index);

		void LoadShaders();

        /**
         * Default initalizes some values, but no actual renderer initalization is done here.
         * To propertly initalize the object call the Init() function
         */
		Renderer2D();

        /**
        * Draw a string the current buffer with the specified font at the specified window position
        * and with the specified colour.
        * 
        * Meaning of position depends on alignment.
        *  [] Left -> X = The text should be drawn horizontally across from this point, Y = text drawn vertically from this point (down)
        *  [] Centre -> X = Position of the centre of the text, Y = text drawn down vertically from this point.
        */
        void DrawString(Font *font,
            const String& text,
            const Vector2& pos,
            const graphics::Color color,
            TextAlignment alignment = TextAlignment::Left 
		);

        /** Draw a circle where the specified position is the centre and the circle consists of `noPoints` number of triangles/points. */
        void FillCircle(Vector2 centrePosition, float radius, const Color& color, size_t noPoints);

        /** Draw the section of a texture (specified by `rect` in UV coordinates) where the width and height of the sprite are specified by `size`. */
        void DrawTextureBounds(Vector3 position, Texture2D* texture, const AABBRectangle& rect, Vector2 size);

        /** Draw the specified texture to the buffer at the specified window coordinates. */
		void DrawTexture(Vector3 position, Texture2D *texture);

        /** Draw a filled rectangle at the specified screen coordinates with the color, width and height specified. */
		void FillRectangle(Vector3 position, float width, float height, const Color& color);

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

        /** Push a transform onto the transformation stack, acting on the next 'draw' call. Does not change the state of the last pushed transformation. */
		void PushTransform(const Matrix4& matrix);

        /** Pop the last transformation off the stack - unless there is only one item left, in which case nothing is done.*/
		void PopTransform();

        /** Set the (view) matrix that is to be multiplied with the projection matrix as a transform that affects the vertex position.*/
        void SetViewMatrix(const Matrix4& view);
        
        void SetProjectionMatrix(const Matrix4& mat);

        static AABBRectangle CoverAllTexture;
    };
}}
