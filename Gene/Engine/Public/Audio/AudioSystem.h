// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Audio/WaveFile.h>

#include <Core/Array.h>
#include <Core/String.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace gene {
	namespace audio {
		class AudioSystem {
		private:
			ALCdevice *m_Device;
			ALCcontext *m_Context;

		public:
			void Init();
			
            /** Get a list of the names of all available OpenAL audio devices.*/
			Array<String> GetAudioDevicesList();

            /** Immediatly play the specified wave file. A non-blocking operation. */
			void PlayWav(WaveFile *wavFile);
		};
	}
}