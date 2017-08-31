#include "ObjectFactory.h"

void ObjectFactory::InitAllTypes()
{
	m_CubeMesh = new GeneModel();
	/*
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	*/
	const float size = 1.f;
	Vector3 vertices[8] = {
		Vector3(-size, -size, size),
		Vector3(size, -size, size),
		Vector3(size, size, size),
		Vector3(-size, size, size),
		/*Vector3(-size, -size, -size),
		Vector3(size, -size, -size),
		Vector3(size, size, -size),
		Vector3(-size, size, -size)*/
	};

	GLuint indices[6 * 6] = {
		/*0, 1, 2, 2, 3, 0,
		3, 2, 6, 6, 7, 3,
		7, 6, 5, 5, 4, 7,
		4, 0, 3, 3, 7, 4,
		0, 1, 5, 5, 4, 0,
		1, 5, 6, 6, 2, 1*/
		0, 1, 2, 2, 3, 0
	};

	float uvMax = 0.125f;

	Vector2 uv[4] = {
		Vector2(uvMax, uvMax),
		Vector2(0, uvMax),
		Vector2(0, 0),
		Vector2(uvMax, 0),
		/*Vector2(0, 0),
		Vector2(uvMax, 0),
		Vector2(uvMax, uvMax),
		Vector2(0, uvMax)*/
	};

	m_CubeMesh->Vertices = std::vector<Vector3>(vertices, vertices + 8);
	m_CubeMesh->Indices = std::vector<GLuint>(indices, indices + (6 * 6));
	m_CubeMesh->UVs = std::vector<Vector2>(uv, uv + 4);
}

Cube ObjectFactory::CreateCube(Vector3 position)
{
	Cube cube(position, m_CubeMesh);
	return cube;
}
