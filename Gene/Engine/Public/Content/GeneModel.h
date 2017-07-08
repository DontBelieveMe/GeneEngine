#pragma once

#include <vector>
#include <Platform/OpenGL.h>
#include <Math/Vector3.h>

namespace Gene { namespace Content {
	class GeneModel {
	public:
		std::vector<Gene::Math::Vector3> Vertices;
		std::vector<Gene::Math::Vector3> Normals;
		std::vector<GLuint> Indices;

	};
}}