// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/RenderDevice.hpp>

using namespace g2;

void RenderDevice::Init(const g2::SharedPtr<IWindow>& window) 
{
	void* windowHandle = window->GetHandle();

	m_context = IOpenGL3Context::CreateContextForThisPlatform(windowHandle);
	m_context->Create();

	SetClearColor(Color::Black);
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
	
BufferHandle RenderDevice::CreateBuffer(size_t initFlags, MemoryRef mem, BufferArrayHandle vao)
{
	BufferHandle handle = m_vertexBufferHandles.Allocate();

	GetBufferArray(vao)->AddBuffer(handle);

	Buffer* buff = GetBuffer(handle);

	G2_GL_CHECK(glBindVertexArray(GetBufferArray(vao)->GetId()));

	buff->Create(initFlags);
	buff->SetData(mem);

	G2_GL_CHECK(glBindVertexArray(0));

	return handle;
}

ShaderHandle RenderDevice::CreateShader(const char* filepath, InputLayoutDef layoutDef)
{
	GraphicsResourceHandle handle = m_shaderHandles.Allocate();
	m_shaders[handle.GetIndex()].Create(filepath, layoutDef);

	return handle;
}

BufferArrayHandle RenderDevice::CreateBufferArray(ShaderHandle shader)
{
	InputLayoutDef layout = m_shaders[shader.GetIndex()].GetInputLayout();
	GLuint programId = m_shaders[shader.GetIndex()].GetProgramId();

	BufferArrayHandle bufferArrayHandle = m_bufferArrayHandles.Allocate();
	BufferArray* vao = &m_bufferArrays[bufferArrayHandle.GetIndex()];
	
	vao->Create();

	G2_GL_CHECK(glBindVertexArray(vao->GetId()));

	const Array<VertexAttribute>& attribs = layout.GetAttributes();
	for (const VertexAttribute& attrib : attribs)
	{
		VertexAttribInputType type = attrib.GetType();

		G2_GL_CHECK(glEnableVertexAttribArray(attrib.GetIndex()));
		G2_GL_CHECK(glBindAttribLocation(programId, attrib.GetIndex(), attrib.GetName()));
		G2_GL_CHECK(glVertexAttribPointer(attrib.GetIndex(), type.NumComponents, type.Type, GL_FALSE, type.Size, (void*)0));
	}

	G2_GL_CHECK(glBindVertexArray(0));

	return bufferArrayHandle;
}