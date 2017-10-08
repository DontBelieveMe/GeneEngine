#pragma once

#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Matrix4.h>

#include <Graphics/Font.h>
#include <Graphics/Color.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Buffer.h>
#include <Graphics/GLSLShader.h>

#include <string>

namespace Gene { namespace Graphics {
    
	struct Vertex 
	{
		Vector3 Position;
		Color	Color;
	};

    class Renderer2D
    {
	private:
		VertexArray *m_VAO;
		Buffer *m_VBO;
		Buffer *m_EBO;
		int m_IndexCount;

		Vertex *m_Buffer;
		GLSLShader *m_Shader;
		Matrix4 m_ProjectionMatrix;

    public:
		Renderer2D();

        void DrawString(Font *font, 
						const std::string& text, 
						const Vector2& pos, 
						const Graphics::Color color
		);

		void DrawRectangle(Vector2 position, float width, float height, const Color& color);

		void Init(const Matrix4& projectionMatrix, GLSLShader *shader);
		void Destroy();

		void Begin();
		void End();
		
		void Present();
    };
}}
