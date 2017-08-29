#pragma once

#include <Graphics/VertexArray.h>
#include <GeneUseAll.h>

struct RenderItem
{
	VertexArray *vao;
	Buffer *ebo;
	Buffer *vbo;
	Buffer *tbo;
};