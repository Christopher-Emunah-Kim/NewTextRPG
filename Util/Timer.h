#pragma once
#include "../Common.h"
#include <chrono>

using TimePoint = std::chrono::steady_clock::time_point;

static constexpr int32 FPS = 60;
static constexpr float TICK_INTERVAL_MS = 1000.0f / (float)FPS - 0.1f;

class Timer final
{
public:
	Timer() = delete;

public:
	static void		Init();
	static bool		CanUpdate();
	static float		GetDeltaTime();

private:
	static TimePoint	m_prevTimePoint;
	static float			m_deltaTime;
	static float			m_timeScale;

};

