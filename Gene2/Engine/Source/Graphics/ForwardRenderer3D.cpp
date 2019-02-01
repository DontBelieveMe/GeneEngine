// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/ForwardRenderer3D.hpp>

using namespace g2;

void ForwardRenderer3D::Render(RenderDevice* renderDevice, BufferArrayHandle vao, ShaderHandle shaders)
{
	BufferArray* pVao = renderDevice->GetBufferArray(vao);
	Shader* pShader = renderDevice->GetShader(shaders);

	G2_GL_CHECK(glUseProgram(pShader->GetProgramId()));
	G2_GL_CHECK(glBindVertexArray(pVao->GetId()));

	// #todo (bwilks) HACK -> HACK -> HACK : only supports 1 buffer (to get things working)
	// look into vertex streams. (bgfx terms)
	Buffer* buff = renderDevice->GetBuffer(pVao->GetBuffers()[0]);
	
	G2_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buff->GetId()));
	Array<VertexAttribute> attribs = pShader->GetInputLayout().GetAttributes();
	for (const VertexAttribute& attrib : attribs)
	{
		VertexAttribInputType type = attrib.GetType();

		G2_GL_CHECK(glEnableVertexAttribArray(attrib.GetIndex()));
		G2_GL_CHECK(glVertexAttribPointer(attrib.GetIndex(), type.NumComponents, type.Type, GL_FALSE, type.Size, (void*)0));
	}
	G2_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	G2_GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	G2_GL_CHECK(glUseProgram(0));
	G2_GL_CHECK(glBindVertexArray(0));
}