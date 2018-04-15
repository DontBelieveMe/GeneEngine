// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/Time.h>
#include <Platform/OS.h>

#include <iostream>

using namespace Gene::Platform;

void Timer::Start()
{
    m_Start = std::chrono::high_resolution_clock::now();
    m_Running = true;
}

void Timer::Stop()
{
    m_Running = false;
}

double Timer::ElapsedTimeSeconds()
{
    if (m_Running) {
        auto x = std::chrono::high_resolution_clock::now() - m_Start;
        auto c = std::chrono::duration_cast<std::chrono::seconds>(x);

        return c.count();
    }
    else {
        return 0;
    }
}

double Timer::ElapsedTimeMs()
{
    if (m_Running) {
        auto x = std::chrono::high_resolution_clock::now() - m_Start;
        auto c = std::chrono::duration_cast<std::chrono::milliseconds>(x);

        return c.count();
    }
    else {
        return 0;
    }
}

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
    m_Delta = m_HasGotEndFrameTime ? delta.count() : 0;
}

void GameTime::EndFrame()
{
    using namespace std::chrono;
    m_EndFrameTime = high_resolution_clock::now();
    auto runningDuration = duration_cast<seconds>(m_EndFrameTime - m_GameStart);
    m_RunningTime = static_cast<float>(runningDuration.count());
    m_HasGotEndFrameTime = true;
}

void GameTime::Init()
{
    m_GameStart = std::chrono::high_resolution_clock::now();
    m_RunningTime = 0; 
	m_Delta = 0;
    m_HasGotEndFrameTime = false;
}
