#include <Content/OBJModel.h>
#include <IO/File.h>
#include <Math/Math.h>

#include <vector>
#include <sstream>

using namespace Gene::Content;

OBJModel::OBJModel(const char *path)
{
	Load(path);
}

OBJModel::~OBJModel()
{

}

void OBJModel::Load(const char *filepath)
{
	using namespace Math;
	using namespace std;

	vector<string> lines = IO::File::ReadLines(filepath);
	
	for (string line : lines)
	{
		// Found comment - skip
		if (line[0] == '#') continue;

		string identifier = line.substr(0, 2);
		if (identifier == "v ")
		{
			istringstream stream(line.substr(2));
			Vector3 vector;
			stream >> vector.X;
			stream >> vector.Y;
			stream >> vector.Z;
		}
		else if (identifier == "f ")
		{

		}

	}
	m_Loaded = true;
}