#pragma once
#include "../Common.h"
#include "../Screen.h"


struct IBehavior
{
	virtual ~IBehavior() = default;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render(Screen* screen) = 0;
	virtual void Release() = 0;

};