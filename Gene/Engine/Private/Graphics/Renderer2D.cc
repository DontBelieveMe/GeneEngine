#include <Graphics/Renderer2D.h>
#include <GeneCommon.h>
#include <Debug/Logger.h>

using namespace Gene::Graphics;
using namespace Gene;

static const int RenderableSize     = sizeof(Vertex2D) * 4; // 4 vertices in a cube
static const int MaxRenderables		= 10000;
static const int RendererBatchSize  = RenderableSize * MaxRenderables;
static const int RendererIndexNum   = MaxRenderables * 6;

static void GenerateRectIndicesIntoBuffer(GLuint *buffer, size_t indicesNum)
{
    GLuint offset = 0;
    for (size_t i = 0; i < indicesNum; i += 6)
    {
        buffer[i] = offset + 0;
        buffer[i + 1] = offset + 1;
        buffer[i + 2] = offset + 2;

        buffer[i + 3] = offset + 2;
        buffer[i + 4] = offset + 3;
        buffer[i + 5] = offset + 0;
        offset += 4;
    }
}

#include "Shaders/Fragment2D.shader"
#include "Shaders/Vertex2D.shader"

Renderer2D::Renderer2D() : m_IndexCount(0) {}

void Renderer2D::Init(const Matrix4& projectionMatrix)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_ProjectionMatrix  = projectionMatrix;
    m_Shader = new GLSLShader;

    // TODO: Fix -> We need a better way of embedding shaders (maybe package in custom package & auto copy/deploy to correct
    // directory
    SHADER_VERTEX2D(vertexShader);
    SHADER_FRAGMENT2D(fragmentShader);

    m_Shader->CompileFromText(vertexShader, fragmentShader);
    m_Shader->Enable();
    
    m_Shader->BindAttributeIndex(0, "position");
    m_Shader->BindAttributeIndex(1, "color");
    m_Shader->BindAttributeIndex(2, "uv");
    m_Shader->BindAttributeIndex(3, "texId");
    
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
    positionAttribDesc.Stride           = sizeof(Vertex2D);
    positionAttribDesc.ByteOfffset      = 0;

    AttributeDescriptor                 colorAttribDesc;
    colorAttribDesc.Index               = 1;
    colorAttribDesc.ComponentCount      = 3;
    colorAttribDesc.Stride              = sizeof(Vertex2D);
	colorAttribDesc.ByteOfffset			= offsetof(Vertex2D, Color);

	AttributeDescriptor					uvAttribDesc;
	uvAttribDesc.Index					= 2;
	uvAttribDesc.ComponentCount			= 2;
	uvAttribDesc.Stride					= sizeof(Vertex2D);
	uvAttribDesc.ByteOfffset			= offsetof(Vertex2D, UV);

	AttributeDescriptor					texIdAttrib;
	texIdAttrib.Index					= 3;
	texIdAttrib.ComponentCount			= 1;
	texIdAttrib.Stride					= sizeof(Vertex2D);
    texIdAttrib.ByteOfffset             = offsetof(Vertex2D, TextureId);

	m_VAO->RegisterAttribute(m_VBO, positionAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, colorAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, uvAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, texIdAttrib);
}

void Renderer2D::DrawTexture(Vector2 position, Texture2D *texture)
{
    if(!texture)
    {
        LOG(Gene::LogLevel::Warning, "DrawTexture() called with a NULL texture parameter. Aborting draw");
        return;
    }

	float width = static_cast<float>(texture->Width());
    float height = static_cast<float>(texture->Height());

    float tid = this->GetTextureSlot(texture);

	m_Texture = texture;
	m_Buffer->Position = Vector3(position, 0.f);
	m_Buffer->UV = Vector2(0, 0);
    m_Buffer->TextureId = tid;
    m_Buffer++;

	m_Buffer->Position = Vector3(position.X + width, position.Y, 0.f);
	m_Buffer->UV = Vector2(1, 0);
    m_Buffer->TextureId = tid;
    m_Buffer++;

	m_Buffer->Position = Vector3(position.X + width, position.Y + height, 0.f);
	m_Buffer->UV = Vector2(1, 1);
    m_Buffer->TextureId = tid;
    m_Buffer++;

	m_Buffer->Position = Vector3(position.X, position.Y + height, 0.f);
	m_Buffer->UV = Vector2(0, 1);
    m_Buffer->TextureId = tid;
    m_Buffer++;

	m_IndexCount += 6;
}

void Renderer2D::DrawString(Font *font, 
						    const std::string &text, 
						    const Math::Vector2& pos, 
							const Graphics::Color color)
{
    if(!font)
    {
        LOG(Gene::LogLevel::Warning, "Font null when trying to draw string '", text, "'! Abandoning draw.");
        return;
    }

    FreeTypeFont *ftFont = font->GetFreeTypeFont();
    Vector3 rgbPack = color.ToNormalizedVector3();
	Texture2D *glTexture = font->GLTexture();
	
	float xPos = pos.X;
	float yPos = pos.Y;

    float tid = GetTextureSlot(glTexture);

	for (size_t i = 0; i < text.length(); i++)
	{
        char c = text[i];
        
        if (c == '\n')
        {
            yPos += ftFont->GetTallestGlyphSize();
            xPos = pos.X;

            continue;
        }

        FreeTypeGlyph *glyph = ftFont->GetGlyph(c);

        GE_ASSERT(glyph != NULL, "Cannot load glyph '%c' Code: %i\n", text[i], static_cast<int>(text[i]));

        float tmpY = yPos - glyph->Offset.Y;
        
        // Work in any kerning
        /*if (i > 0) {
            Vector2 kerning = ftFont->GetKerning(text[i - 1], c);
        //    xPos += kerning.X;
        }*/

        m_Buffer->Position  = Vector3(xPos, tmpY, 0.f);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = glyph->UV_TopLeft;
        m_Buffer->TextureId = tid;
        m_Buffer++;

        m_Buffer->Position  = Vector3(xPos + glyph->Width, tmpY, 0.f);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = glyph->UV_TopRight;
        m_Buffer->TextureId = tid;
        m_Buffer++;

        m_Buffer->Position  = Vector3(xPos + glyph->Width, tmpY + glyph->Height, 0.f);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = glyph->UV_BottomRight;
        m_Buffer->TextureId = tid;
        m_Buffer++;

        m_Buffer->Position  = Vector3(xPos, tmpY + glyph->Height, 0.f);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = glyph->UV_BottomLeft;
        m_Buffer->TextureId = tid;
        m_Buffer++;

		xPos += glyph->Advance.X;

		m_IndexCount += 6;
	}
}

float Renderer2D::GetTextureSlot(Texture2D *texture)
{
    GE_ASSERT(m_Textures.size() <= 32);
    GE_ASSERT(m_Textures.size() >= 0);

    for(size_t i = 0; i < m_Textures.size(); i++)
    {
        if(texture == m_Textures[i])
        {
            return static_cast<float>(i);
        }
    }

    // The texture is not in the list...
    m_Textures.push_back(texture);
    return m_Textures.size() - 1.f;
}

void Renderer2D::FillRectangle(Vector2 position, float width, float height, const Color& color)
{
    Vector3 rgbCol = color.ToNormalizedVector3();

	m_Buffer->Position = Vector3(position, 0.f);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = -1;
    m_Buffer++;
	
	m_Buffer->Position = Vector3(position.X + width, position.Y, 0.f);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = -1;
    m_Buffer++;

	m_Buffer->Position = Vector3(position.X + width, position.Y + height, 0.f);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = -1;
    m_Buffer++;

	m_Buffer->Position = Vector3(position.X, position.Y + height, 0.f);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = -1;
    m_Buffer++;

	m_IndexCount += 6;
}

void Renderer2D::Begin()
{
	m_VAO->Enable();
    m_Buffer = m_VBO->GetPointer<Vertex2D>();

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

    for(size_t i = 0; i < m_Textures.size(); i++)
    {
        m_Textures[i]->Enable(i);
    }

    m_VAO->DebugDrawElements(m_EBO, m_IndexCount);

    for(size_t i = 0; i < m_Textures.size(); i++)
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
