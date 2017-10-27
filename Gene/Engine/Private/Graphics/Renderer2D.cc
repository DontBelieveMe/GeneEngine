#include <Graphics/Renderer2D.h>
#include <GeneCommon.h>

#include "FreetypeGL.h"

using namespace Gene::Graphics;
using namespace Gene;

static const int RenderableSize     = sizeof(Vertex) * 4; // 4 vertices in a cube
static const int MaxRenderables		= 10000;
static const int RendererBatchSize  = RenderableSize * MaxRenderables;
static const int RendererIndexNum   = MaxRenderables * 6;

#define VERTEX_TYPE_FONT 1
#define VERTEX_TYPE_NON_FONT -1

static void GenerateRectIndicesIntoBuffer(GLuint *buffer, int indicesNum)
{
    GLuint offset = 0;
    for (GLuint i = 0; i < indicesNum; i += 6)
    {
        buffer[i] = offset + 0;
        buffer[i+1] = offset + 1;
        buffer[i+2] = offset + 2;

        buffer[i + 3] = offset + 2;
        buffer[i + 4] = offset + 3;
        buffer[i + 5] = offset + 0;
        offset += 4;
    }
}

Renderer2D::Renderer2D() : m_IndexCount(0) {}

void Renderer2D::Init(const Matrix4& projectionMatrix)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_ProjectionMatrix  = projectionMatrix;
    m_Shader = new GLSLShader;
    m_Shader->CompileFromFiles("Data/vertex2d.glsl", "Data/fragment2d.glsl");
    m_Shader->Enable();

    m_Shader->BindAttributeIndex(0, "position");
    m_Shader->BindAttributeIndex(1, "color");
    m_Shader->BindAttributeIndex(2, "uv");
    m_Shader->BindAttributeIndex(3, "texId");
    m_Shader->BindAttributeIndex(4, "vertexType");

	m_Shader->LoadUniformMatrix4f("u_Projection", projectionMatrix);

	GLint texIds[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	m_Shader->LoadUniform1iv("textureSamplers", texIds, 10);

	m_VAO = new VertexArray;
    m_VAO->Enable();

    m_VBO = new Buffer(Buffer::Type::ArrayBuffer);
    m_EBO = new Buffer(Buffer::Type::ElementBuffer);

    BufferDescriptor                    desc;
    desc.Data                           = NULL;
    desc.DataType                       = OpenGL::GLType::Float;
    desc.DrawType                       = BufferDrawType::Dynamic;
    desc.Size                           = RendererBatchSize;
	m_VBO->SetData(desc);

    GLuint *indices                     = new GLuint[RendererIndexNum];

    GenerateRectIndicesIntoBuffer(indices, RendererIndexNum);

    BufferDescriptor                    eboDesc;
    eboDesc.Data                        = indices;
    eboDesc.DataType                    = OpenGL::GLType::UnsignedInt;
    eboDesc.DrawType                    = BufferDrawType::Static;
    eboDesc.Size                        = RendererIndexNum;
	m_EBO->SetData(eboDesc);

    AttributeDescriptor                 positionAttribDesc;
    positionAttribDesc.Index            = 0;
    positionAttribDesc.ComponentCount   = 3;
    positionAttribDesc.Stride           = sizeof(Vertex);
    positionAttribDesc.ByteOfffset      = 0;

    AttributeDescriptor                 colorAttribDesc;
    colorAttribDesc.Index               = 1;
    colorAttribDesc.ComponentCount      = 3;
    colorAttribDesc.Stride              = sizeof(Vertex);
	colorAttribDesc.ByteOfffset			= offsetof(Vertex, Color);

	AttributeDescriptor					uvAttribDesc;
	uvAttribDesc.Index					= 2;
	uvAttribDesc.ComponentCount			= 2;
	uvAttribDesc.Stride					= sizeof(Vertex);
	uvAttribDesc.ByteOfffset			= offsetof(Vertex, UV);

	AttributeDescriptor					texIdAttrib;
	texIdAttrib.Index					= 3;
	texIdAttrib.ComponentCount			= 1;
	texIdAttrib.Stride					= sizeof(Vertex);
    texIdAttrib.ByteOfffset             = offsetof(Vertex, TextureId);

    AttributeDescriptor					vertxTypeAttribDesc;
    vertxTypeAttribDesc.Index           = 4;
    vertxTypeAttribDesc.ComponentCount  = 1;
    vertxTypeAttribDesc.Stride          = sizeof(Vertex);
    vertxTypeAttribDesc.ByteOfffset     = offsetof(Vertex, VertexType);

	m_VAO->RegisterAttribute(m_VBO, positionAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, colorAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, uvAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, texIdAttrib);
    m_VAO->RegisterAttribute(m_VBO, vertxTypeAttribDesc);
}

void Renderer2D::DrawTexture(Vector2 position, Texture2D *texture)
{
	float width = texture->Width();
    float height = texture->Height();

    float tid = this->GetTextureSlot(texture);

	m_Texture = texture;
	m_Buffer->Position = Vector3(position, 0.f);
	m_Buffer->UV = Vector2(0, 0);
    m_Buffer->TextureId = tid;
    m_Buffer->VertexType = VERTEX_TYPE_NON_FONT;
	m_Buffer++;

	m_Buffer->Position = Vector3(position.X + width, position.Y, 0.f);
	m_Buffer->UV = Vector2(1, 0);
    m_Buffer->TextureId = tid;
    m_Buffer->VertexType = VERTEX_TYPE_NON_FONT;
    m_Buffer++;

	m_Buffer->Position = Vector3(position.X + width, position.Y + height, 0.f);
	m_Buffer->UV = Vector2(1, 1);
    m_Buffer->TextureId = tid;
    m_Buffer->VertexType = VERTEX_TYPE_NON_FONT;
	m_Buffer++;

	m_Buffer->Position = Vector3(position.X, position.Y + height, 0.f);
	m_Buffer->UV = Vector2(0, 1);
    m_Buffer->TextureId = tid;
    m_Buffer->VertexType = VERTEX_TYPE_NON_FONT;
	m_Buffer++;

	m_IndexCount += 6;
}

void Renderer2D::DrawString(Font *font, 
						    const std::string &text, 
						    const Math::Vector2& pos, 
							const Graphics::Color color)
{
	using namespace ftgl;

	texture_font_t *ftFont = font->TextureFont();
	ColorRGB rgbPack = color.GetRGBStruct();

	Texture2D *glTexture = font->GLTexture();
	
	float xPos = pos.X;
	float yPos = pos.Y;

    float tid = GetTextureSlot(glTexture);

	for (size_t i = 0; i < text.length(); i++)
	{
        char c = text[i];
		ftgl::texture_glyph_t *glyph = texture_font_get_glyph(ftFont, &c);

		GE_ASSERT(glyph != NULL, "Cannot load glyph '%c' Code: %i\n", text[i], (int)text[i]);
        float tmpY = yPos - glyph->offset_y;

        m_Buffer->Position  = Vector3(xPos, tmpY, 0.f);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = Vector2(glyph->s0, glyph->t0);
        m_Buffer->TextureId = tid;
        m_Buffer->VertexType = VERTEX_TYPE_FONT;
		m_Buffer++;

        m_Buffer->Position  = Vector3(xPos + glyph->width, tmpY, 0.f);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = Vector2(glyph->s1, glyph->t0);
        m_Buffer->TextureId = tid;
        m_Buffer->VertexType = VERTEX_TYPE_FONT;
		m_Buffer++;

        m_Buffer->Position  = Vector3(xPos + glyph->width, tmpY + glyph->height, 0.f);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = Vector2(glyph->s1, glyph->t1);
        m_Buffer->TextureId = tid;
        m_Buffer->VertexType = VERTEX_TYPE_FONT;
        m_Buffer++;

        m_Buffer->Position  = Vector3(xPos, tmpY + glyph->height, 0.f);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = Vector2(glyph->s0, glyph->t1);
        m_Buffer->TextureId = tid;
        m_Buffer->VertexType = VERTEX_TYPE_FONT;
        m_Buffer++;

		xPos += glyph->advance_x;

		m_IndexCount += 6;
	}
}

float Renderer2D::GetTextureSlot(Texture2D *texture)
{
    GE_ASSERT(m_Textures.size() <= 32);
    GE_ASSERT(m_Textures.size() >= 0);

    for(int i = 0; i < m_Textures.size(); i++)
    {
        if(texture == m_Textures[i])
        {
            return static_cast<float>(i);
        }
    }

    // The texture is not in the list...
    m_Textures.push_back(texture);
    return m_Textures.size() - 1;
}

void Renderer2D::FillRectangle(Vector2 position, float width, float height, const Color& color)
{
    ColorRGB rgbCol = color.GetRGBStruct();

	m_Buffer->Position = Vector3(position, 0.f);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = -1;
    m_Buffer->VertexType = VERTEX_TYPE_NON_FONT;
    m_Buffer++;
	
	m_Buffer->Position = Vector3(position.X + width, position.Y, 0.f);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = -1;
    m_Buffer->VertexType = VERTEX_TYPE_NON_FONT;
    m_Buffer++;

	m_Buffer->Position = Vector3(position.X + width, position.Y + height, 0.f);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = -1;
    m_Buffer->VertexType = VERTEX_TYPE_NON_FONT;
    m_Buffer++;

	m_Buffer->Position = Vector3(position.X, position.Y + height, 0.f);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = -1;
    m_Buffer->VertexType = VERTEX_TYPE_NON_FONT;
    m_Buffer++;

	m_IndexCount += 6;
}

void Renderer2D::Begin()
{
	m_VAO->Enable();
    m_Buffer = m_VBO->GetPointer<Vertex>();

    GE_ASSERT(m_Buffer);
}

void Renderer2D::End()
{
	m_VAO->Disable();
	m_VBO->UnmapPointer();
}

void Renderer2D::Present()
{
	m_Shader->Enable();

    for(int i = 0; i < m_Textures.size(); i++)
    {
        m_Textures[i]->Enable(i);
    }

    m_VAO->DebugDrawElements(m_EBO, m_IndexCount);

    for(int i = 0; i < m_Textures.size(); i++)
    {
        m_Textures[i]->Disable(i);
    }

    m_IndexCount = 0;
	m_Shader->Disable();

    m_Textures.clear();
}

void Renderer2D::Destroy()
{
	delete m_VAO;
	delete m_VBO;
}
