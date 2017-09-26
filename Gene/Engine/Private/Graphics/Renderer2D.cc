#include <Graphics/Renderer2D.h>
#include "FreetypeGL.h"

using namespace Gene::Graphics;
using namespace Gene;

static const int RenderableSize     = sizeof(Vertex) * 4; // 4 vertices in a cube
static const int MaxRenderables		= 100;
static const int RendererBatchSize  = RenderableSize * MaxRenderables;

void Renderer2D::Init()
{
	m_VAO = new VertexArray;
	m_VBO = new Buffer(Buffer::Type::ArrayBuffer);
	
	BufferDescriptor desc;
	desc.Data = NULL;
	desc.DataType = OpenGL::GLType::Float;
	desc.DrawType = BufferDrawType::Dynamic;
	desc.Size = RendererBatchSize;
	m_VBO->SetData(desc);

	AttributeDescriptor attribDesc;
	attribDesc.ByteOfffset 

	m_VAO->RegisterAttribute(m_VBO, )

	m_VBO->Enable();

	m_Buffer = m_VBO->GetPointer<Vertex>();
	m_Buffer->Position.X = 1;
	m_Buffer->Position.Y = 2;
	m_Buffer->Position.Z = 3;
	m_Buffer++;
	m_VBO->Disable();
}

void Renderer2D::DrawString(Font *font, 
						    const std::string &text, 
						    const Math::Vector2& pos, 
							const Graphics::Color color)
{
	using namespace ftgl;

	texture_font_t *ftFont = font->TextureFont();

}

void Renderer2D::Present()
{
	m_VAO->Enable();

	m_VAO->Disable();
}
