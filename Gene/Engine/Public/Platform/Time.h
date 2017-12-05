#pragma once
#include <chrono>

namespace Gene { namespace Platform {
	class GameTime {
    private:
        typedef std::chrono::time_point<std::chrono::high_resolution_clock> GameClock;

        float     m_Delta;
        float     m_RunningTime;
		float m_RunningTimeMs;

        GameClock m_StartFrameTime;
        GameClock m_EndFrameTime;
        GameClock m_GameStart;

	public:
        void Init();

        float DeltaInMilliSeconds() const { return m_Delta; }
        float RunningTimeSeconds()  const { return m_RunningTime; }
        float RunningTimeMilliseconds() const;

        void  StartFrame();
        void  EndFrame();

        void  Sleep(float milliseconds);
	};
}}
