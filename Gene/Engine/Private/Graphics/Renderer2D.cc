#include <Graphics/Renderer2D.h>
#include "FreetypeGL.h"

using namespace Gene::Graphics;
using namespace Gene;

static const int RenderableSize     = sizeof(Vertex) * 4; // 4 vertices in a cube
static const int MaxRenderables		= 100;
static const int RendererBatchSize  = RenderableSize * MaxRenderables;
static const int RendererIndexNum   = MaxRenderables * 6;

Renderer2D::Renderer2D() : m_IndexCount(0) {}

void Renderer2D::Init(const Matrix4& projectionMatrix, GLSLShader * shader)
{
	m_ProjectionMatrix = projectionMatrix;
	m_Shader = shader;

	m_Shader->Enable();
	m_Shader->LoadUniformMatrix4f("u_Projection", projectionMatrix);
	
	m_VAO = new VertexArray;
	m_VBO = new Buffer(Buffer::Type::ArrayBuffer);
	m_EBO = new Buffer(Buffer::Type::ElementBuffer);

	m_VAO->Enable();
	
	BufferDescriptor desc;
	desc.Data = NULL;
	desc.DataType = OpenGL::GLType::Float;
	desc.DrawType = BufferDrawType::Dynamic;
	desc.Size = RendererBatchSize;
	m_VBO->SetData(desc);

	GLuint *indices = new GLuint[RendererIndexNum];
	GLuint offset = 0;
	for (GLuint i = 0; i < RendererIndexNum; i += 6)
	{
		indices[i] = offset + 0;
		indices[i+1] = offset + 1;
		indices[i+2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;
		offset += 4;
	}

	BufferDescriptor eboDesc;
	eboDesc.Data = indices;
	eboDesc.DataType = OpenGL::GLType::UnsignedInt;
	eboDesc.DrawType = BufferDrawType::Static;
	eboDesc.Size = RendererIndexNum;
	m_EBO->SetData(eboDesc);

	AttributeDescriptor positionAttribDesc;
	positionAttribDesc.Index = 0;
	positionAttribDesc.ComponentCount = 3;
	positionAttribDesc.Stride = sizeof(Vertex);
	positionAttribDesc.ByteOfffset = 0;

	AttributeDescriptor colorAttribDesc;
	colorAttribDesc.Index = 1;
    colorAttribDesc.ComponentCount = 1;
	colorAttribDesc.Stride = sizeof(Vertex);
	colorAttribDesc.ByteOfffset = sizeof(Vector3);

	m_VAO->RegisterAttribute(m_VBO, positionAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, colorAttribDesc);
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

void Renderer2D::DrawRectangle(Vector2 position, float width, float height, const Color& color)
{
    ColorRGB rgbCol = color.GetRGBStruct();

	m_Buffer->Position = Vector3(position, 0.f);
    m_Buffer->Color = rgbCol;
	m_Buffer++;
	
	m_Buffer->Position = Vector3(position.X + width, position.Y, 0.f);
    m_Buffer->Color = rgbCol;
	m_Buffer++;

	m_Buffer->Position = Vector3(position.X + width, position.Y + height, 0.f);
    m_Buffer->Color = rgbCol;
	m_Buffer++;

	m_Buffer->Position = Vector3(position.X, position.Y + height, 0.f);
    m_Buffer->Color = rgbCol;
	m_Buffer++;

	m_IndexCount += 6;
}

void Renderer2D::Begin()
{
	m_VAO->Enable();
	m_Buffer = m_VBO->GetPointer<Vertex>();
}

void Renderer2D::End()
{
	m_VAO->Disable();
	m_VBO->UnmapPointer();
}

void Renderer2D::Present()
{
	m_Shader->Enable();
	m_VAO->Enable();
    m_VBO->Enable();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE, sizeof(Vertex),
        0
    );

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE, sizeof(Vertex),
        (const GLvoid*) sizeof(Vector3)
    );
    int i = glGetError();

    m_EBO->Enable();
    m_VAO->DebugDrawElements(m_EBO, m_IndexCount);

	m_IndexCount = 0;
    m_EBO->Disable();
    m_VAO->Disable();
	m_Shader->Disable();
}

void Renderer2D::Destroy()
{
	delete m_VAO;
	delete m_VBO;
}
