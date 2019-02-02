// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/RenderDevice.hpp>

using namespace g2;

void RenderDevice::Init(const g2::SharedPtr<IWindow>& window) 
{
	void* windowHandle = window->GetHandle();

	m_context = IOpenGL3Context::CreateContextForThisPlatform(windowHandle);
	m_context->Create();

	SetClearColor(Color::Black);

	G2_GL_CHECK(glGenVertexArrays(1, &m_gVao));
	G2_GL_CHECK(glBindVertexArray(m_gVao));
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
	
BufferHandle RenderDevice::CreateBuffer(size_t initFlags, MemoryRef mem)
{
	BufferHandle handle = m_vertexBufferHandles.Allocate();

	Buffer* buff = GetBuffer(handle);

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

void RenderDevice::DrawPrimitive(ShaderHandle shader, BufferHandle buffer, size_t numPrimitives)
{
	Shader* pShader = GetShader(shader);
	Buffer* pBuffer = GetBuffer(buffer);
	
	G2_GL_CHECK(glUseProgram(pShader->GetProgramId()));
	G2_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, pBuffer->GetId()));

	const Array<VertexAttribute> attribs = pShader->GetInputLayout().GetAttributes();
	for (const VertexAttribute& attrib : attribs)
	{
		VertexAttribInputType type = attrib.GetType();

		G2_GL_CHECK(glEnableVertexAttribArray(attrib.GetIndex()));
		G2_GL_CHECK(glVertexAttribPointer(attrib.GetIndex(), type.NumComponents, type.Type, GL_FALSE, type.Size, (void*)0));
	}

	const int NUM_ELEMENTS_IN_TRIANGLE = 3;
	const size_t numElements = numPrimitives * NUM_ELEMENTS_IN_TRIANGLE;

	G2_GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, numElements));
}