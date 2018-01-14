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

#include <string>
#include <vector>

namespace Gene { namespace Graphics {
    
	struct Vertex 
	{
        Vector3     Position;
        Vector3     Color;
        Vector2     UV;
        float       TextureId;
        float       VertexType;
	};

    class Renderer2D
    {
	private:
        VertexArray             *m_VAO;
        Buffer                  *m_VBO;
        Buffer                  *m_EBO;
        int                      m_IndexCount;

        Vertex                  *m_Buffer;
        GLSLShader              *m_Shader;
        Matrix4                  m_ProjectionMatrix;
        Texture2D               *m_Texture;
        std::vector<Texture2D*>  m_Textures;

    private:
        float GetTextureSlot(Texture2D *texture);

	public:
		Renderer2D();

        void DrawString(Font *font, 
						const std::string& text, 
						const Vector2& pos, 
						const Graphics::Color color
		);

		void DrawTexture(Vector2 position, Texture2D *texture);
		void FillRectangle(Vector2 position, float width, float height, const Color& color);

        void Init(const Matrix4& projectionMatrix);
		void Destroy();

		void Begin();
		void End();
		
		void Present();
    };
}}
