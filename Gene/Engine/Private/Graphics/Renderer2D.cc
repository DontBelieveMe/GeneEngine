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

	m_VAO->Enable();
	
	BufferDescriptor desc;
	desc.Data = new float[123];
	desc.DataType = OpenGL::GLType::Float;
	desc.DrawType = BufferDrawType::Dynamic;
	desc.Size = RendererBatchSize;
	m_VBO->SetData(desc);

	AttributeDescriptor positionAttribDesc;
	positionAttribDesc.Index = 0;
	positionAttribDesc.ComponentCount = 3;
	positionAttribDesc.Stride = 3 * sizeof(GLfloat);
	positionAttribDesc.ByteOfffset = 0;

	m_VAO->RegisterAttribute(m_VBO, positionAttribDesc);

	Vertex *data = m_VBO->GetPointer<Vertex>();

	m_VBO->UnmapPointer();
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
