#include "ObjectFactory.h"

void ObjectFactory::InitAllTypes()
{
	m_CubeMesh = new GeneModel();

	const float size = 1.f;
	Vector3 vertices[8] = {
		Vector3(-size, -size, size),
		Vector3(size, -size, size),
		Vector3(size, size, size),
		Vector3(-size, size, size),
		Vector3(-size, -size, -size),
		Vector3(size, -size, -size),
		Vector3(size, size, -size),
		Vector3(-size, size, -size)
	};

	GLuint indices[6 * 6] = {
		0, 1, 2, 2, 3, 0,
		3, 2, 6, 6, 7, 3,
		7, 6, 5, 5, 4, 7,
		4, 0, 3, 3, 7, 4,
		0, 1, 5, 5, 4, 0,
		1, 5, 6, 6, 2, 1
	};

	Vector2 uv[8] = {
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1),
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	m_CubeMesh->Vertices = std::vector<Vector3>(vertices, vertices + 8);
	m_CubeMesh->Indices = std::vector<GLuint>(indices, indices + (6 * 6));
	m_CubeMesh->UVs = std::vector<Vector2>(uv, uv + 8);
}

Cube ObjectFactory::CreateCube(Vector3 position)
{
	Cube cube(position, m_CubeMesh);
	return cube;
}
