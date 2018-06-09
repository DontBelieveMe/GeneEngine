// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Runtime/Resources.h>
#include <cstdint>

#include <AL/al.h>

namespace gene { namespace audio {
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
        /** Load the audio file and create initalize it's OpenAL source id.*/
		void			Load(const char *filepath);

        /** Free any resources used by this object. */
		virtual void	Destroy();

        /** Set if the audio file should loop -> e.g immediatly start playing again after it has stopped continiously.*/
		void			Loop(bool shouldLoop);

        /** Set the gain of this audio file. */
		void			SetGain(float gain);

        /** Return a bool static whether this audio file is being played or not currently.*/
		bool			IsPlaying();

        /** Return the OpenAL source id of this audio file.*/
		ALuint			GetSourceId() const { return m_SourceId; }
	};
}}