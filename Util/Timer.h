#pragma once
#include "../Common.h"

using TimePoint = std::chrono::steady_clock::time_point;

static constexpr int32 FPS = 60;
static constexpr float TICK_INTERVAL_MS = 1000.0f / static_cast<float>(FPS) - 0.1f;

class Timer
{
public:
	Timer() = delete;

private:
	static TimePoint	m_prevTimePoint;
	static float		m_deltaTime;
	static float		m_timeScale;
	

public:
	static void		Init();
	static bool		CanUpdate();
	static float	GetDeltaTime();

};

