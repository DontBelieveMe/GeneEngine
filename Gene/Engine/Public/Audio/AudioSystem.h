// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Audio/WaveFile.h>

#include <Core/Array.h>
#include <Core/String.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace Gene {
	namespace Audio {
		class AudioSystem {
		private:
			ALCdevice *m_Device;
			ALCcontext *m_Context;

		public:
			void Init();
			
			Array<String> GetAudioDevicesList();

			void PlayWav(WaveFile *wavFile);
		};
	}
}