#pragma once
#include <chrono>

namespace Gene { namespace Platform {
	class GameTime {
	private:
		float m_Delta;
        float m_RunningTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartFrameTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_EndFrameTime;

        std::chrono::time_point<std::chrono::high_resolution_clock> m_GameStart;

	public:
        void Init();

		float DeltaInMilliSeconds() const {return m_Delta; }
        float RunningTimeSeconds() const { return m_RunningTime; }

		void StartFrame();
        void EndFrame();

        void Sleep(float milliseconds);
	};
}}
