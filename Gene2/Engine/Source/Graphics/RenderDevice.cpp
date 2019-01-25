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
	
Buffer* RenderDevice::CreateBuffer(size_t initFlags)
{
	Buffer buff;
	buff.Create(initFlags);
	m_buffers.push_back(buff);
	return &m_buffers.back();
}

Shader* RenderDevice::CreateShader(const char* filepath)
{
	Shader *shader = new Shader;
	shader->Create(filepath);
	return shader;
}