#include "Timer.h"



void Timer::Init()
{
	m_deltaTime = 0.0f;
	m_timeScale = 1.0f;
	m_prevTimePoint = high_resolution_clock::now();
}


bool Timer::CanUpdate()
{
	TimePoint current = high_resolution_clock::now();
}

float Timer::GetDeltaTime()
{
	return m_deltaTime * m_timeScale;
}