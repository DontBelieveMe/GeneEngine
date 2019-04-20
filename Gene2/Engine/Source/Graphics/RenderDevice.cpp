// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/RenderDevice.hpp>
#include <Gene2/Debug/Assert.hpp>
#include <numeric>

using namespace g2;

void RenderDevice::Init(const g2::SharedPtr<IWindow>& window) 
{
	void* windowHandle = window->GetHandle();

	m_context = IOpenGL3Context::CreateContextForThisPlatform(windowHandle, m_ctxAttribs);
	m_context->Create();

	SetClearColor(Color::Black);

	G2_GL_CHECK(glGenVertexArrays(1, &m_gVao));
	G2_GL_CHECK(glBindVertexArray(m_gVao));

	G2_GL_CHECK(glEnable(GL_DEPTH_TEST));
	G2_GL_CHECK(glDepthFunc(GL_LESS));
}

void RenderDevice::SetUniformValue(UniformHandle uniform, void* value)
{
	Uniform& uniformData = m_uniforms[uniform.GetIndex()];
	
	Shader* shader = GetShaderPtr(uniformData.Shader);
	G2_GL_CHECK(glUseProgram(shader->GetProgramId()));
	
	switch (uniformData.Type)
	{
	case UNIFORM_TYPE_MAT4:
		glUniformMatrix4fv(uniformData.CachedLocation, 1, GL_TRUE, (float*)value);
		break;
	case UNIFORM_TYPE_VEC2:
	{
		float* fdata = (float*)value;
		glUniform2f(uniformData.CachedLocation, fdata[0], fdata[1]);
		break;
	}
	case UNIFORM_TYPE_VEC3:
	{
		float* fdata = (float*)value;
		glUniform3f(uniformData.CachedLocation, fdata[0], fdata[1], fdata[2]);
		break;
	}
	case UNIFORM_TYPE_VEC4:
	{
		float* fdata = (float*)value;
		glUniform4f(uniformData.CachedLocation, fdata[0], fdata[1], fdata[2], fdata[3]);
		break;
	}
	case UNIFORM_TYPE_SAMPLER_2D:
		break;
	default: // Note: Should never happen
		G2_ASSERT(false, "Cannot set uniform with invalid type");
		break;
	}
	G2_GL_CHECK(glUseProgram(0));
}

UniformHandle RenderDevice::CreateUniform(ShaderHandle shader, const char* uniformName, EUniformType uniformType)
{
	UniformHandle handle = m_uniformHandles.Allocate();
	Uniform& uniform = m_uniforms[handle.GetIndex()];

	Shader* shaderPtr = GetShaderPtr(shader);

	uniform.CachedLocation = G2_GL_CHECK(glGetUniformLocation(shaderPtr->GetProgramId(), uniformName));
	uniform.Name = uniformName;
	uniform.Shader = shader;
	uniform.Type = uniformType;

	return handle;
}

void RenderDevice::SetContextAttribute(EContextAttribute attribute, int value)
{
	switch (attribute)
	{
	case CA_GL_MAJOR_VERSION:
		m_ctxAttribs.TargetMajorVersion = value;
		break;
	case CA_GL_MINOR_VERSION:
		m_ctxAttribs.TargetMinorVersion = value;
		break;
	case CA_GL_PROFILE:
		m_ctxAttribs.Profile = value;
		break;
	default:
		G2_ASSERT(false, "Cannot set context attribute {0} that does not exist", (int)attribute);
		break;
	}
}

void RenderDevice::SetClearColor(const Color& color)
{
	G2_GL_CHECK(glClearColor(
		color.GetNormalizedRed(),
		color.GetNormalizedGreen(),
		color.GetNormalizedBlue(),
		color.GetNormalizedAlpha()
	));
}

void RenderDevice::Clear(u32 flags)
{
	G2_GL_CHECK(glClear(flags));
}

void RenderDevice::SwapBuffers()
{
	m_context->SwapBuffers();
}

void RenderDevice::SetVertexBuffer(int streamIndex, BufferHandle handle, int stride, int offset) 
{
	m_streams[streamIndex].VertexBuffer = handle;
	m_streams[streamIndex].Stride = stride;
	m_streams[streamIndex].Offset = offset;
}

BufferHandle RenderDevice::CreateBuffer(size_t initFlags, MemoryRef mem)
{
	BufferHandle handle = m_vertexBufferHandles.Allocate();

	Buffer* buff = GetBufferPtr(handle);

	buff->Create(initFlags);
	buff->SetData(mem);

	return handle;
}

ShaderHandle RenderDevice::CreateShader(const char* filepath, InputLayoutDef layoutDef)
{
	GraphicsResourceHandle handle = m_shaderHandles.Allocate();
	m_shaders[handle.GetIndex()].Create(filepath, layoutDef);

	return handle;
}

TextureHandle RenderDevice::CreateTexture(const char* filepath)
{
	GraphicsResourceHandle tex = m_textureHandles.Allocate();
	m_textures[tex.GetIndex()].Create(filepath);

	return tex;
}

void RenderDevice::SetTexture(TextureHandle handle, int slot)
{
	Texture* tex = &m_textures[handle.GetIndex()];
	
	G2_GL_CHECK(glActiveTexture(GL_TEXTURE0 + slot));
	G2_GL_CHECK(glBindTexture(GL_TEXTURE_2D, tex->GetId()));
}

Buffer* RenderDevice::GetBufferPtr(BufferHandle handle)
{
	return &m_vertexBuffers[handle.GetIndex()];
}

Shader* RenderDevice::GetShaderPtr(ShaderHandle handle)
{
	return &m_shaders[handle.GetIndex()];
}

void RenderDevice::DrawPrimitive(ShaderHandle shader, size_t numPrimitives)
{
	Shader* pShader = GetShaderPtr(shader);
	G2_GL_CHECK(glUseProgram(pShader->GetProgramId()));

	const Array<VertexAttribute>& attribs = pShader->GetInputLayout().GetAttributes();
	
	for (const VertexAttribute& attrib : attribs)
	{
		VertexStream& stream = m_streams[attrib.GetStreamIndex()];

		G2_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffers[stream.VertexBuffer.GetIndex()].GetId()));

		VertexAttribInputType type = attrib.GetType();

		G2_GL_CHECK(glEnableVertexAttribArray(attrib.GetIndex()));
		G2_GL_CHECK(glVertexAttribPointer(
			attrib.GetIndex(), 
			type.NumComponents, 
			type.Type, GL_FALSE, 
			stream.Stride, (const GLvoid*)(std::uintptr_t)(stream.Offset + attrib.GetOffset())
		));
	}

	G2_GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, numPrimitives));
}