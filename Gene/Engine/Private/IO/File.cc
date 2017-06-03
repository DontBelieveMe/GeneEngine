#include <Platform/OS.h>

#if defined(GENE_OS_WINDOWS) && defined(GENE_COMPILER_MSVC) 
	#define _CRT_SECURE_NO_WARNINGS 
#endif

#include <IO/File.h>

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace Gene::IO;

File::~File()
{
	Free();
}

File::File(const char *filepath)
{
	if (filepath != nullptr)
	{
		Load(filepath);
	}
}

void File::Load(const char *filepath)
{
	if (m_Data != nullptr) return;

	FILE *file = fopen(filepath, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int len = ftell(file);
		fseek(file, 0, SEEK_SET);
		m_Data = new char[len + 1];
		if (m_Data)
		{
			fread(m_Data, 1, len, file);
			m_Data[len] = '\0';
		}
		fclose(file);
	}
}

void File::Free()
{
	delete[] m_Data;
}

std::vector<std::string> File::ReadLines(const char *path)
{
	using namespace std;
	vector<string> lines;

	ifstream file(path);
	string line;
	while (getline(file, line))
	{
		lines.push_back(line);
	}

	return lines;
}
