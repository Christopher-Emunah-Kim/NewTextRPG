#pragma once
#include "../Common.h"

struct IBehavior
{
	virtual ~IBehavior() = default;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

};