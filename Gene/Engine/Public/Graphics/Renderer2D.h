#pragma once

#include <Math/Vector2.h>
#include <Math/Vector3.h>

#include <Graphics/Font.h>
#include <Graphics/Color.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Buffer.h>

#include <string>

namespace Gene { namespace Graphics {
    
	struct Vertex 
	{
		Math::Vector3 Position;
	};

    class Renderer2D
    {
	private:
		VertexArray *m_VAO;
		Buffer *m_VBO;
		Vertex *m_Buffer;

    public:
        void DrawString(Font *font, 
						const std::string& text, 
						const Math::Vector2& pos, 
						const Graphics::Color color
		);

		void Init();
		void Destroy();
		void Present();
    };
}}
