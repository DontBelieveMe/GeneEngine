#include <Content/OBJModelLoader.h>
#include <IO/File.h>
#include <Math/Vector3.h>

#include <sstream>

using namespace Gene::Content;

GeneModel *OBJModelLoader::Load(const char * filepath)
{
	using namespace Gene::IO;
	using namespace Gene::Math;


	std::vector<std::string> lines = File::ReadLines(filepath);

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
		}
	}
	return nullptr;
}