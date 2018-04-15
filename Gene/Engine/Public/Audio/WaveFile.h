// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Runtime/Resources.h>
#include <cstdint>

#include <AL/al.h>

namespace Gene { namespace Audio {
	class WaveFile : public IResource {
	private:
		int				m_AudioFormat;
		int				m_NumChannels;
		int				m_SampleRate;
		int				m_ByteRate;
		int				m_BlockAlign;
		int				m_BitsPerSample;

		uint8_t		   *m_AudioData;
		int			    m_AudioDataSize;

		ALuint			m_SourceId;
		ALuint  		m_BufferId;

		ALenum			GetALFormat();

	public:
		void			Load(const char *filepath);
		virtual void	Destroy();

		void			Loop(bool shouldLoop);
		void			SetGain(float gain);

		bool			IsPlaying();

		ALuint			GetSourceId() const { return m_SourceId; }
	};
}}