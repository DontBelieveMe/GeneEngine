// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Audio/WaveFile.h>
#include <IO/File.h>
#include <GeneCommon.h>

#include <string.h>

using namespace gene::audio;
using namespace gene::io;

struct Header {
	uint8_t ID[4];
	uint32_t Size;
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

	int offset = 0;
	do {
		Header header2;
		memcpy(&header2, fileData + offset, sizeof(Header));
		offset += sizeof(Header);

		if (IsHeader(header2, "fmt ")) {
			FMTChunk chunk;
			memcpy(&chunk, fileData + offset, header2.Size);
			m_AudioFormat = chunk.AudioFormat;
			m_NumChannels = chunk.NumChannels;
			m_SampleRate = chunk.SampleRate;
			m_ByteRate = chunk.ByteRate;
			m_BlockAlign = chunk.BlockAlign;
			m_BitsPerSample = chunk.BitsPerSample;
		}
		else if (IsHeader(header2, "data")) {
			m_AudioData = new uint8_t[header2.Size];
			memset(m_AudioData, 0, header2.Size);
			m_AudioDataSize = header2.Size;
			memcpy(m_AudioData, fileData + offset, header2.Size);
			break;
		}
		else if (IsHeader(header2, "RIFF")) {
			offset += 4;
			continue;
		}

		offset += header2.Size;
	} while (true);

	delete[] fileData;

	alGenSources(1, &m_SourceId);
	
	alSourcef(m_SourceId, AL_PITCH, 1);
	alSourcef(m_SourceId, AL_GAIN, 1);
	alSource3f(m_SourceId, AL_POSITION, 0, 0, 0);
	alSource3f(m_SourceId, AL_VELOCITY, 0, 0, 0);
	alSourcei(m_SourceId, AL_LOOPING, AL_FALSE);

	alGenBuffers(1, &m_BufferId);
	alBufferData(m_BufferId, GetALFormat(), m_AudioData, m_AudioDataSize, m_SampleRate);
	alSourcei(m_SourceId, AL_BUFFER, m_BufferId);
}

ALenum WaveFile::GetALFormat()
{
	bool isStereo = m_NumChannels > 1;

	switch (m_BitsPerSample)
	{
	case 16:
		return isStereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
	case 8:
		return isStereo ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO8;
	default:
		GE_ASSERT(false, "Unknown OpenAL audio format: Bits Per Sample=", m_BitsPerSample);
		return -1;
	}
	return 0;
}

void WaveFile::Destroy()
{
	alSourceStop(m_SourceId);
	alDeleteSources(1, &m_SourceId);
	alDeleteBuffers(1, &m_BufferId);
	delete[] m_AudioData;
}

void WaveFile::Loop(bool shouldLoop)
{
	alSourcef(m_SourceId, AL_LOOPING, static_cast<ALfloat>(shouldLoop ? AL_TRUE : AL_FALSE));
}

void WaveFile::SetGain(float gain)
{
	alSourcef(m_SourceId, AL_GAIN, gain);
}

bool WaveFile::IsPlaying()
{
	ALenum state;
	alGetSourcei(m_SourceId, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}
