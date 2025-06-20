#pragma once
#include "../../Common.h"


enum class EInputEvent
{
	NONE = 0,
	PRESSED,
	RELEASED,
	HOLD,
	MAX_COUNT
};


enum class EMoveDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX_COUNT
};