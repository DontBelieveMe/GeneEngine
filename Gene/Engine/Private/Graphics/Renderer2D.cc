#include <Graphics/Renderer2D.h>
#include "FreetypeGL.h"

using namespace Gene::Graphics;
using namespace Gene;

static const int RenderableSize     = sizeof(Vertex) * 4; // 4 vertices in a cube
static const int MaxRenderables		= 100;
static const int RendererBatchSize  = RenderableSize * MaxRenderables;

void Renderer2D::Init(const Matrix4& projectionMatrix)
{
	m_ProjectionMatrix = projectionMatrix;

	m_VAO = new VertexArray;
	m_VBO = new Buffer(Buffer::Type::ArrayBuffer);

	m_VAO->Enable();
	
	BufferDescriptor desc;
	desc.Data = NULL;
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

	m_Buffer = m_VBO->GetPointer<Vertex>();
}

void Renderer2D::DrawString(Font *font, 
						    const std::string &text, 
						    const Math::Vector2& pos, 
							const Graphics::Color color)
{
	using namespace ftgl;

	texture_font_t *ftFont = font->TextureFont();

	for (size_t i = 0; i < text.length(); i++)
	{

	}
}

void Renderer2D::Present()
{
	m_VAO->Enable();

	m_VAO->Disable();
}

void Renderer2D::Destroy()
{
	m_VBO->UnmapPointer();

	delete m_VAO;
	delete m_VBO;
}