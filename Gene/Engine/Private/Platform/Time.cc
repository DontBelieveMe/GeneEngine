#include <Platform/Time.h>
#include <Platform/OS.h>

#include <iostream>

using namespace Gene::Platform;

void GameTime::StartFrame()
{
	using namespace std::chrono;
	m_StartFrameTime = high_resolution_clock::now();
    duration<float, std::milli> delta = duration_cast<milliseconds>(m_StartFrameTime - m_EndFrameTime);
	m_Delta = delta.count();
}

void GameTime::EndFrame()
{
    using namespace std::chrono;
    m_EndFrameTime = high_resolution_clock::now();
    auto runningDuration = duration_cast<seconds>(m_EndFrameTime - m_GameStart);
    m_RunningTime = runningDuration.count();
}

void GameTime::Init()
{
    m_GameStart = std::chrono::high_resolution_clock::now();
}
