#pragma once

#include <Platform/OpenGL.h>
#include <Math/Vector3.h>
#include <Math/Vector2.h>
#include <Core/Array.h>

namespace Gene { namespace Content {
	class GeneModel {
	public:
		Array<Vector3> Vertices;
        Array<Vector3> Normals;
        Array<Vector2> UVs;
        Array<GLuint> Indices;
	};
}}