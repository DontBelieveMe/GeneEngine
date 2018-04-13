#include <Audio/AudioSystem.h>
#include <GeneCommon.h>
#include <Debug/Logger.h>

using namespace Gene::Audio;
using namespace Gene;

Array<String> AudioSystem::GetAudioDevicesList()
{
	const ALCchar *device = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	const ALCchar *next = device + 1;
	size_t len = 0;

	Array<String> devices;

	while (device && *device != '\0' && next && *next != '\0')
	{
		devices.push_back(device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}

	return devices;
}

void AudioSystem::Init()
{
	m_Device = alcOpenDevice(NULL);
	GE_ASSERT(m_Device);

	m_Context = alcCreateContext(m_Device, NULL);
	ALCboolean s = alcMakeContextCurrent(m_Context);
	GE_ASSERT(s);

	alListener3f(AL_POSITION, 0, 0, 0.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerf(AL_GAIN, 1.0f);

#ifndef NDEBUG
	Array<String> devices = this->GetAudioDevicesList();

	LOG(LogLevel::Infomation, "|------------------------");
	LOG(LogLevel::Infomation, "| Available Audio Devices");
	LOG(LogLevel::Infomation, "|------------------------");
	for (const String& device : devices)
	{
		LOG(LogLevel::Infomation, "|\t", device);
	}
	LOG(LogLevel::Infomation, "|------------------------");
#endif
}

void AudioSystem::PlayWav(WaveFile *wavFile)
{
	ALCenum s = alcGetError(m_Device);

	alSourcePlay(wavFile->GetSourceId());
}