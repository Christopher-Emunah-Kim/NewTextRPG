#include "Timer.h"

TimePoint Timer::m_prevTimePoint;
float Timer::m_deltaTime = 0.0f;
float Timer::m_timeScale = 1.0f;


void Timer::Init()
{
	m_prevTimePoint = high_resolution_clock::now();
}


bool Timer::CanUpdate()
{
	TimePoint current = high_resolution_clock::now();

	duration<float> elapsed = current - m_prevTimePoint; 

	if (TICK_INTERVAL_MS * 0.001f > elapsed.count())
	{
		return false;
	}

	m_deltaTime = elapsed.count();

	m_prevTimePoint = current;
	
	return true;
}
