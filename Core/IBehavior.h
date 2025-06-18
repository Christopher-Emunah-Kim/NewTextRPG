#pragma once
#include "../Common.h"

_INTERFACE IBehavior
{
	virtual ~IBehavior() = default;

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

};