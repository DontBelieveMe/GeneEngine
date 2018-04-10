// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/Time.h>
#include <Platform/OS.h>

#include <iostream>

using namespace Gene::Platform;

float GameTime::RunningTimeMilliseconds() const
{
    auto x = std::chrono::high_resolution_clock::now() - m_GameStart;
    auto c = std::chrono::duration_cast<std::chrono::milliseconds>(x);

    return static_cast<float>(c.count());
}

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
    m_RunningTime = static_cast<float>(runningDuration.count());
}

void GameTime::Init()
{
    m_GameStart = std::chrono::high_resolution_clock::now();
	m_Delta = 0;
}
