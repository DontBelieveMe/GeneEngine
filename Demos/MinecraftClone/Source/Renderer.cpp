#include "Renderer.h"

#include <Platform/OpenGL.h>

void Renderer::SubmitMesh(GameObject *mesh)
{
	GeneModel *model = mesh->Mesh;

	RenderItem item;
	item.vao = new VertexArray;

	Buffer *vbo = new Buffer(Buffer::Type::ArrayBuffer);
	Buffer *tbo = new Buffer(Buffer::Type::ArrayBuffer);
	Buffer *ibo = new Buffer(Buffer::Type::ElementBuffer);
	item.vao->Enable();

	BufferDescriptor vboDesc;
	vboDesc.Data = &(model->Vertices[0]);
	vboDesc.DataType = GLType::Float;
	vboDesc.Size = model->Vertices.size() * 3 * sizeof(GLfloat);
	vboDesc.DrawType = BufferDrawType::Static;
	vbo->SetData(vboDesc);

	BufferDescriptor uvDesc;
	uvDesc.Data = &(model->UVs[0]);
	uvDesc.DataType = GLType::Float;
	uvDesc.Size = model->UVs.size() * 2 * sizeof(GLfloat);
	uvDesc.DrawType = BufferDrawType::Static;
	tbo->SetData(uvDesc);

	BufferDescriptor iboDesc;
	iboDesc.Data = &(model->Indices[0]);
	iboDesc.DataType = GLType::UnsignedInt;
	iboDesc.Size = model->Indices.size() * sizeof(GLuint);
	iboDesc.DrawType = BufferDrawType::Static;
	ibo->SetData(iboDesc);

	AttributeDescriptor vertexAttrib;
	vertexAttrib.Index = 0;
	vertexAttrib.ComponentCount = 3;
	vertexAttrib.Stride = 0;
	vertexAttrib.ByteOfffset = 0;

	AttributeDescriptor uvAttrib;
	uvAttrib.Index = 0;
	uvAttrib.ComponentCount = 3;
	uvAttrib.Stride = 2;
	uvAttrib.ByteOfffset = 0;

	item.vao->RegisterAttribute(vbo, vertexAttrib);
	item.vao->RegisterAttribute(tbo, uvAttrib);

	item.ebo = ibo;
	item.vbo = vbo;
	item.tbo = tbo;

	m_Objects.push_back(mesh);
	mesh->DrawInfo = item;
}

void Renderer::Draw()
{
	m_Shaders.Standard->Enable();

	for (GameObject* item : m_Objects)
	{
		Matrix4 transform = Matrix4::Identity();
		transform.Translate(item->Position);
		Vector3& rotation = item->Rotation;
		transform.RotateX(rotation.X);
		transform.RotateY(rotation.Y);
		transform.RotateZ(rotation.Z);
		m_Shaders.Standard->LoadUniformMatrix4f("u_Transform", transform);
		item->DrawInfo.vao->DebugDrawElements(item->DrawInfo.ebo);
	}
	m_Shaders.Standard->Disable();
}