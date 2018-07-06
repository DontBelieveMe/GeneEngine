// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/OS.h>

#if defined(GENE_OS_WINDOWS) && defined(GENE_COMPILER_MSVC) 
	#define _CRT_SECURE_NO_WARNINGS 
#endif

#include <IO/File.h>

#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#include <GeneCommon.h>
#include <Core/Array.h>

using namespace gene::io;
using namespace gene;

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
	} else 
    {
        printf("Cannot find resource %s\n", filepath);
        GE_ASSERT(false, "File::Load(...) Cannot load file at path: ", filepath);
    }
}

void File::Free()
{
	delete[] m_Data;
}

uint8_t * File::LoadBinaryFile(const char * path)
{
	FILE *file = fopen(path, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int len = ftell(file);
		fseek(file, 0, SEEK_SET);
		uint8_t *data = new uint8_t[len + 1];
		if (data)
		{
			fread(data, 1, len, file);
		}
		fclose(file);
		return data;
	}
	else
	{
		GE_ASSERT(false, "Cannot open binary file: ", path);
	}

	return nullptr;
}

Array<String> File::ReadLines(const char *path)
{
	Array<String> lines;

	std::ifstream file(path);
	if (file.is_open())
	{
		String line;
		while (getline(file, line))
		{
			lines.push_back(line);
		}
	}
	else 
    {
		GE_ASSERT(false, "Cannot read lines in from file: ", path);
	}

	return lines;
}
