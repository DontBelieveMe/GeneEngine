// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Graphics/Renderer2D.h>
#include <GeneCommon.h>
#include <Debug/Logger.h>
#include <string>
#include <Platform/OpenGL.h> 

#include <iostream>

#include "Shaders/Fragment2D.shader" 
#include "Shaders/Vertex2D.shader" 

using namespace gene::graphics;
using namespace gene;

static const int RenderableSize     = sizeof(Vertex2D) * 4; // 4 vertices in a cube
static const int MaxRenderables		= 10000;
static const int RendererBatchSize  = RenderableSize * MaxRenderables;
static const int RendererIndexNum   = MaxRenderables * 6;
 
#define RENDERER_NO_TEXTURE_ID -1.0f 

Renderer2D::Renderer2D() 
    : m_IndexCount(0), m_IndexOffset(0) 
{}

void Renderer2D::SetViewMatrix(const Matrix4& view)
{
    m_Shader->Enable();
    m_Shader->LoadUniformMatrix4f("u_View", view);
    m_Shader->Disable();
}

void Renderer2D::SetProjectionMatrix(const Matrix4 & mat)
{
    m_Shader->Enable();
    m_Shader->LoadUniformMatrix4f("u_Projection", mat);
    m_Shader->Disable();
}

void Renderer2D::LoadShaders()
{
	m_Shader->CompileFromFiles("Data/Shaders/Renderer2DVertex.shader", "Data/Shaders/Renderer2DFragment.shader");
	m_Shader->Enable();

	int textureValues[] = { 0,1,2,3,4,5,6,7,8,9 };

	m_Shader->LoadUniform1iv("u_Textures", textureValues, 9);

	m_Shader->BindAttributeIndex(0, "in_Position");
	m_Shader->BindAttributeIndex(1, "in_Color");
	m_Shader->BindAttributeIndex(2, "in_TextureUV");
	m_Shader->BindAttributeIndex(3, "in_SamplerIndex");

	m_Shader->LoadUniformMatrix4f("u_Projection", m_ProjectionMatrix);

	SetViewMatrix(Matrix4::Identity());

	
	m_Shader->Disable();
}


void Renderer2D::LoadLight(Light* light, int index)
{
	m_Shader->LoadUniform3f(String("u_Lights[" + ToString(index) + "].Position").c_str(), light->Position);
	m_Shader->LoadUniform3f(String("u_Lights[" + ToString(index) + "].Color").c_str(), light->Colour.ToNormalizedVector3());
	m_Shader->LoadUniform1f(String("u_Lights[" + ToString(index) + "].Size").c_str(), light->Size);
	m_Shader->LoadUniform1f(String("u_Lights[" + ToString(index) + "].Intensity").c_str(), light->Intensity);
	m_Shader->LoadUniform1f(String("u_Lights[" + ToString(index) + "].Falloff").c_str(), light->Falloff);
}

void Renderer2D::LoadLights(Array<Light*>& lights)
{
	Light *DEFAULT_LIGHT = new Light;
	m_Lights.reserve(4);
	DEFAULT_LIGHT->Colour = Color::White;
	DEFAULT_LIGHT->Falloff = -1.0f;
	DEFAULT_LIGHT->Intensity = -1.0f;
	DEFAULT_LIGHT->Position = Vector3();
	DEFAULT_LIGHT->Size = -1.f;

	m_Shader->Enable();
	for (int i = 0; i < 4; i++) 
	{
		if (i < lights.size())
		{
			LoadLight(lights[i], i);
		}
		else {
			LoadLight(DEFAULT_LIGHT, i);
		}
	}
	m_Shader->Disable();
	m_Lights = lights;
}

void Renderer2D::Init(const Matrix4& projectionMatrix)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ZERO);
    m_ProjectionMatrix  = projectionMatrix;
    m_Shader = new GLSLShader;
    
	LoadShaders();
	m_Shader->Enable();
    
	m_VAO = new VertexArray;
    m_VAO->Enable(); 

    m_VBO = new Buffer(Buffer::Type::ArrayBuffer);
    m_EBO = new Buffer(Buffer::Type::ElementBuffer); 
	 
    BufferDescriptor                    desc;
    desc.Data                           = NULL;
    desc.DataType                       = opengl::GLType::Float;
    desc.DrawType                       = BufferDrawType::Dynamic;
    desc.Size                           = RendererBatchSize;
	m_VBO->SetData(desc);

    GLuint *indices                     = new GLuint[RendererIndexNum];

    BufferDescriptor                    eboDesc;
    eboDesc.Data                        = indices;
    eboDesc.DataType                    = opengl::GLType::UnsignedInt;
    eboDesc.DrawType                    = BufferDrawType::Dynamic;
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

	AttributeDescriptor					samplerIndexAttrib;
	samplerIndexAttrib.Index					= 3;
	samplerIndexAttrib.ComponentCount			= 1;
	samplerIndexAttrib.Stride					= sizeof(Vertex2D);
	samplerIndexAttrib.ByteOfffset             = offsetof(Vertex2D, TextureId);

	m_VAO->RegisterAttribute(m_VBO, positionAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, colorAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, uvAttribDesc);
	m_VAO->RegisterAttribute(m_VBO, samplerIndexAttrib);
	 
	m_TransformationStack.push_back(Matrix4::Identity(1.0f));
}

void Renderer2D::PushTransform(const Matrix4& matrix)
{
	if (m_TransformationStack.empty())
	{ 
		m_TransformationStack.push_back(Matrix4::Identity(1.0f));
	}

	Matrix4 back = m_TransformationStack.back();

	m_TransformationStack.push_back(back * matrix);
	m_TransformationStack[m_TransformationStack.size() - 1].Elements[3 + 3 * 4] = 1.f;
}

void Renderer2D::PopTransform()
{
    if (m_TransformationStack.size() > 1)
    {
        m_TransformationStack.pop_back(); 
    }
}

Vector3 MultiplyVector2ByMatrix4(float x, float y, const Matrix4& mat4)
{
    return mat4.Multiply(Vector3(x, y, 1.0f));
}

void Renderer2D::DrawTextureBounds(Vector3 position, Texture2D *texture, const AABBRectangle& rect, Vector2 size)
{
    if (!texture)
    {
        LOG(LogLevel::Warning, "DrawTextureBounds() called with a NULL texture parameter. Aborting draw");
        return;
    }

    float width = size.X;
    float height = size.Y;

    float tid = this->GetTextureSlot(texture);

    const Matrix4& backTransform = m_TransformationStack.back();

    m_Buffer->Position = MultiplyVector2ByMatrix4(position.X, position.Y, backTransform);
    m_Buffer->UV = rect.TopLeft;
    m_Buffer->TextureId = tid;
    m_Buffer->Color = Vector3(1.0f, 1.0f, 1.0f);
    m_Buffer++;

    m_Buffer->Position = MultiplyVector2ByMatrix4(position.X + width, position.Y, backTransform);
    m_Buffer->UV = rect.TopRight;
    m_Buffer->TextureId = tid;
    m_Buffer->Color = Vector3(1.0f, 1.0f, 1.0f);
    m_Buffer++;

    m_Buffer->Position = MultiplyVector2ByMatrix4(position.X + width, position.Y + height, backTransform);
    m_Buffer->UV = rect.BottomRight;
    m_Buffer->TextureId = tid;
    m_Buffer->Color = Vector3(1.0f, 1.0f, 1.0f);
    m_Buffer++;

    m_Buffer->Position = MultiplyVector2ByMatrix4(position.X, position.Y + height, backTransform);
    m_Buffer->UV = rect.BottomLeft;
    m_Buffer->TextureId = tid;
    m_Buffer->Color = Vector3(1, 1, 1);
    m_Buffer++;

    WriteRectangleIndices();
}

AABBRectangle Renderer2D::CoverAllTexture = AABBRectangle({ 0,0 }, { 1, 0 }, {0, 1}, {1, 1});

void Renderer2D::DrawTexture(Vector3 position, Texture2D *texture)
{
    DrawTextureBounds(position, texture, CoverAllTexture, { (float)texture->Width(), (float)texture->Height() });
}

void Renderer2D::DrawString(Font *font, 
						    const String& text, 
						    const Vector2& pos, 
							const graphics::Color color,
                            TextAlignment alignment)
{
    if(!font)
    {
        LOG(LogLevel::Warning, "Font null when trying to draw string '", text, "'! Abandoning draw.");
        return;
    }

    FreeTypeFont *ftFont = font->GetFreeTypeFont();
    Vector3 rgbPack = color.ToNormalizedVector3();
	Texture2D *glTexture = font->GLTexture();
	
	float xPos = pos.X;
	float yPos = pos.Y;

    float tid = GetTextureSlot(glTexture);
	
	float spaceWidth = font->MeasureString(" ").X;
	const int TAB_SIZE = 4;	// 1 tab is 4 spaces.

    Matrix4 backTransform = m_TransformationStack.back();

    Array<Vector2> lineSizes = font->MeasureLines(text);
    float longestLineLength = font->MeasureString(text).X;
    
    if (alignment == TextAlignment::Centre)
    {
        float diff = (longestLineLength / 2) - (lineSizes[0].X / 2);
        xPos += diff;
    }

    int lineIndex = 0;
	for (size_t i = 0; i < text.length(); i++)
	{
        char c = text[i];
        
        if (c == '\n')
        {
            lineIndex++;
            yPos += ftFont->GetTallestGlyphSize();
            float diff = 0;
            
            if(alignment == TextAlignment::Centre)
                diff = (longestLineLength / 2) - (lineSizes[lineIndex].X / 2);

            xPos = pos.X + diff;

            continue;
		}
		else if (c == '\t')
		{
			xPos += spaceWidth * TAB_SIZE;
			continue;
		}

        FreeTypeGlyph *glyph = ftFont->GetGlyph(c);

        GE_ASSERT(glyph != NULL, "Cannot load glyph '%c' Code: %i\n", text[i], static_cast<int>(text[i]));

        float tmpY = yPos - glyph->Offset.Y;
 
       // Work in any kerning
        if (i > 0) {
            Vector2 kerning = ftFont->GetKerning(text[i - 1], c);
            xPos += kerning.X;
        }
        
        m_Buffer->Position  = MultiplyVector2ByMatrix4(xPos, tmpY, backTransform);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = glyph->UV_TopLeft;
        m_Buffer->TextureId = tid;
        m_Buffer++;

        m_Buffer->Position  = MultiplyVector2ByMatrix4(xPos + glyph->Width + 1, tmpY, backTransform);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = glyph->UV_TopRight;
        m_Buffer->TextureId = tid;
        m_Buffer++;

        m_Buffer->Position  = MultiplyVector2ByMatrix4(xPos + glyph->Width + 1, tmpY + glyph->Height + 1, backTransform);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = glyph->UV_BottomRight;
        m_Buffer->TextureId = tid;
        m_Buffer++;

        m_Buffer->Position  = MultiplyVector2ByMatrix4(xPos, tmpY + glyph->Height + 1, backTransform);
        m_Buffer->Color     = rgbPack;
        m_Buffer->UV        = glyph->UV_BottomLeft;
        m_Buffer->TextureId = tid;
        m_Buffer++;

		xPos += glyph->Advance.X;

        WriteRectangleIndices();
	}
}

float Renderer2D::GetTextureSlot(Texture2D *texture)
{
	for (size_t i = 0; i < m_Textures.size(); i++) {
		if (m_Textures[i] == texture) {
			return static_cast<float>(i);
		}
	}

	float size = static_cast<float>(m_Textures.size());
	m_Textures.push_back(texture);
	return size;
}

void Renderer2D::FillCircle(Vector2 position, float radius, const Color& color, size_t noPoints)
{
    if(!m_Buffer || !m_Indices) return;
    
    if (noPoints < 3) {
        LOG(LogLevel::Debug, "Trying to draw circle with less than 3 points");
        return;
    }
    
    Vector3 rgbCol = color.ToNormalizedVector3();
    Matrix4 backTransform = m_TransformationStack.back();
    
    float segmentSize = Maths::ToRadians(360.f / noPoints);

    for (size_t i = 0; i < noPoints; ++i)
    {
        float angle = segmentSize * i;
        Vector2 pos(
            radius * Maths::Cos(angle) + position.X,
            radius * Maths::Sin(angle) + position.Y
        );

        m_Buffer->Position = MultiplyVector2ByMatrix4(pos.X, pos.Y, backTransform);
        m_Buffer->Color = rgbCol;
        m_Buffer->TextureId = RENDERER_NO_TEXTURE_ID;
        m_Buffer++;

        angle = segmentSize * (i + 1);
        pos = Vector2(
            radius * Maths::Cos(angle) + position.X,
            radius * Maths::Sin(angle) + position.Y
        );

        m_Buffer->Position = MultiplyVector2ByMatrix4(pos.X, pos.Y, backTransform);
        m_Buffer->Color = rgbCol;
        m_Buffer->TextureId = RENDERER_NO_TEXTURE_ID;
        m_Buffer++;

        m_Buffer->Position = MultiplyVector2ByMatrix4(position.X, position.Y, backTransform);;
        m_Buffer->Color = rgbCol;
        m_Buffer->TextureId = RENDERER_NO_TEXTURE_ID;
        m_Buffer++;

        /*
         * TODO: We don't really index this shape as well as we could -> e.g Middle position (common to all triangles) is not indexed (I think) and there
         *       will be some duplication around the outside (e.g 2 triangles share at least one common vertex with another triangle)
         *     
         *              Triangle 1 : Vertex 0 -> Vertex 1
         *              Triangle 2 : Vertex 1 -> Vertex 2
         *              Triangle 3 : Vertex 2 -> Vertex 3
         *              etc...
         *
         *      this should be fixed, or be considered if circles are too slow to draw.
         */

        *m_Indices = m_IndexOffset + 0;
        *(++m_Indices) = m_IndexOffset + 1;
        *(++m_Indices) = m_IndexOffset + 2;
        m_Indices++;
        m_IndexCount += 3;
        m_IndexOffset += 3;
    }
}

void Renderer2D::WriteRectangleIndices()
{
    *m_Indices = m_IndexOffset + 0;
    *(++m_Indices) = m_IndexOffset + 1;
    *(++m_Indices) = m_IndexOffset + 2;

    *(++m_Indices) = m_IndexOffset + 2;
    *(++m_Indices) = m_IndexOffset + 3;
    *(++m_Indices) = m_IndexOffset + 0;

    m_Indices++;
    m_IndexCount += 6;
    m_IndexOffset += 4;
}



void Renderer2D::FillRectangle(Vector3 position, float width, float height, const Color& color)
{
    Vector3 rgbCol = color.ToNormalizedVector3();
    Matrix4 backTransform = m_TransformationStack.back();

	m_Buffer->Position = MultiplyVector2ByMatrix4(position.X, position.Y, backTransform);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = RENDERER_NO_TEXTURE_ID;
    m_Buffer++;
	
	m_Buffer->Position = MultiplyVector2ByMatrix4(position.X + width, position.Y, backTransform);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = RENDERER_NO_TEXTURE_ID;
    m_Buffer++;

	m_Buffer->Position = MultiplyVector2ByMatrix4(position.X + width, position.Y + height, backTransform);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = RENDERER_NO_TEXTURE_ID;
    m_Buffer++;

	m_Buffer->Position = MultiplyVector2ByMatrix4(position.X, position.Y + height, backTransform);
    m_Buffer->Color = rgbCol;
    m_Buffer->TextureId = RENDERER_NO_TEXTURE_ID;
    m_Buffer++;

    WriteRectangleIndices();
}

void Renderer2D::Begin()
{
    m_VAO->Enable();
    m_Buffer = m_VBO->GetPointer<Vertex2D>();

    m_Indices = m_EBO->GetPointer<unsigned int>();
    //GE_ASSERT(m_Indices);
}

void Renderer2D::End()
{
	m_VAO->Disable();
	m_VBO->UnmapPointer();
    m_EBO->UnmapPointer();
}

void Renderer2D::Present()
{
	m_Shader->Enable();

    for(size_t i = 0; i < m_Textures.size(); i++)
    {
        m_Textures[i]->Enable(i);
	}
	
	m_VAO->Enable();
	m_EBO->Enable();

    m_VAO->DrawElements(m_EBO, m_IndexCount);

	m_VAO->Disable();
	m_EBO->Disable();

    for(size_t i = 0; i < m_Textures.size(); i++)
    {
        m_Textures[i]->Disable(i);
    }
    
    m_IndexCount = 0;
    m_IndexOffset = 0;
	m_Shader->Disable();

    m_Textures.clear();
}

void Renderer2D::Destroy()
{
	delete m_VAO;
	delete m_VBO;
    delete m_EBO;
}
