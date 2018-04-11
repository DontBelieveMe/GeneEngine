// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Audio/WaveFile.h>
#include <IO/File.h>

#include <string.h>

using namespace Gene::Audio;
using namespace Gene::IO;

struct Header {
	uint8_t ID[4];
	uint32_t Size;
};

struct RIFFHeader {
	Header Header;
	uint8_t Format[4];
};

struct FMTChunk {
	uint16_t AudioFormat;
	uint16_t NumChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;
	uint16_t BlockAlign;
	uint16_t BitsPerSample;
};

struct DataChunk {
	uint8_t *Data;
};

static bool IsHeader(const Header& header, const char *id)
{
	return header.ID[0] == id[0] && header.ID[1] == id[1] && header.ID[2] == id[2] && header.ID[3] == id[3];
}

void WaveFile::Load(const char *filepath)
{
	uint8_t *fileData = File::LoadBinaryFile(filepath);

	RIFFHeader header;
	memcpy(&header, fileData, sizeof(RIFFHeader));

	int offset = sizeof(RIFFHeader);
	
	do {
		Header header;
		memcpy(&header, fileData + offset, sizeof(Header));
		offset += sizeof(Header);

		if (IsHeader(header, "fmt ")) {
			FMTChunk chunk;
			memcpy(&chunk, fileData + offset, header.Size);
			m_AudioFormat = chunk.AudioFormat;
			m_NumChannels = chunk.NumChannels;
			m_SampleRate = chunk.SampleRate;
			m_ByteRate = chunk.ByteRate;
			m_BlockAlign = chunk.BlockAlign;
			m_BitsPerSample = chunk.BitsPerSample;
		}
		else if (IsHeader(header, "data")) {
			m_AudioData = new uint8_t[header.Size];
			m_AudioDataSize = header.Size;
			memcpy(m_AudioData, fileData + header.Size, header.Size);
			break;
		}

		offset += header.Size;
	} while (true);

	delete[] fileData;
}