#pragma once

#include <vector>
#include <Platform/OpenGL.h>
#include <Math/Vector3.h>

namespace Gene { namespace Content {
	class GeneModel {
	public:
		std::vector<Math::Vector3> Vertices;
		std::vector<Math::Vector3> Normals;
		std::vector<GLuint>		   Indices;

		GeneModel(std::vector<Math::Vector3> vertice, std::vector<Math::Vector3> normals, std::vector<GLuint> indices);
	};
}}