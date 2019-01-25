#define _CRT_SECURE_NO_WARNINGS

#include <Gene2/Core/StdLib/File.hpp>
#include <Gene2/Debug/Assert.hpp>

#include <cstdio>

using namespace g2;

String File::ReadAllText(const char* filepath)
{
	FILE *file = fopen(filepath, "r");

	G2_ASSERT(file, "File '{0}' does not exist. Could not open.", filepath);

	fseek(file, 0, SEEK_END);
	const int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	String outputString;
	outputString.resize(fileSize);
	fread(&outputString[0], 1, fileSize, file);
	fclose(file);

	return outputString;
}