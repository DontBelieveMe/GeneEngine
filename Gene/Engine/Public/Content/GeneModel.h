#pragma once

#include <vector>
#include <Platform/OpenGL.h>
#include <Math/Vector3.h>
#include <Math/Vector2.h>
#include <GeneCommon.h>

namespace Gene { namespace Content {
	class GeneModel {
	public:
		Array<Gene::Math::Vector3> Vertices;
        Array<Gene::Math::Vector3> Normals;
        Array<Gene::Math::Vector2> UVs;
        Array<GLuint> Indices;
	};
}}