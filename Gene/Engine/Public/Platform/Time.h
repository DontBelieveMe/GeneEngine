#pragma once
#include <chrono>

namespace Gene { namespace Platform {
	class GameTime {
	private:
		float m_Delta;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartFrameTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_EndFrameTime;

	public:
		float DeltaInMilliSeconds() const {return m_Delta; }

		void StartFrame();
		void EndFrame();
	};
}}