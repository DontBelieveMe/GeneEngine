#include <Content/OBJModelLoader.h>
#include <IO/File.h>
#include <Math/Vector3.h>
#include <Platform/OpenGL.h>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace Gene::Content;

GeneModel *OBJModelLoader::Load(const char * filepath)
{
	using namespace Gene::IO;
	using namespace Gene::Math;


	std::vector<std::string> lines = File::ReadLines(filepath);

	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<GLuint> indices;

	for (std::string line : lines)
	{
		std::string id = line.substr(0, 2);
		if (id == "v ") 
		{
			std::istringstream stream(line.substr(2));
			Vector3 vector;
			stream >> vector.X;
			stream >> vector.Y;
			stream >> vector.Z;
			vertices.push_back(vector);
		}
		else if (id == "f ")
		{
			std::istringstream stream(line.substr(2));
			GLuint a, b, c;
			stream >> a;
			stream >> b;
			stream >> c;
			a--; b--; c--;
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);
		}
	}

	normals.resize(vertices.size(), { 0.f, 0.f, 0.f });
    int x = *(std::max_element(indices.begin(), indices.end()));
	for (int i = 0; i < indices.size(); i+=3)
	{
		GLuint ia = indices[i];
		GLuint ib = indices[i + 1];
		GLuint ic = indices[i + 2];

		Vector3 q = vertices[ib];
		Vector3 r = vertices[ic];
		Vector3 p = vertices[ia];

		Vector3 normal = Vector3::CrossProduct(
			q - p,
			r - p
		);

		normal.Normalize();
		normals[ia] = normals[ib] = normals[ic] = normal;
	}

	GeneModel *model = new GeneModel();
	model->Vertices = vertices;
	model->Normals = normals;
	model->Indices = indices;

	return model;
}
