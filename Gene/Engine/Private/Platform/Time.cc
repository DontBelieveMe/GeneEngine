#include <Platform/Time.h>
#include <iostream>
using namespace Gene::Platform;

void GameTime::StartFrame()
{
	using namespace std::chrono;
	m_StartFrameTime = high_resolution_clock::now();
	auto delta = duration_cast<milliseconds>(m_StartFrameTime - m_EndFrameTime);
	m_Delta = delta.count();
}

void GameTime::EndFrame() {
	m_EndFrameTime = std::chrono::high_resolution_clock::now();
}