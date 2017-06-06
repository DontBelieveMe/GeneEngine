#include <Content/GeneModel.h>
#include <Math/Vector3.h>
using namespace Gene::Content;

GeneModel::GeneModel(std::vector<Math::Vector3> vertices,
					 std::vector<Math::Vector3> normals, 
				     std::vector<GLuint> indices) 
{
	Vertices = vertices;
	Normals = normals;
	Indices = indices;
}