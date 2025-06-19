#pragma once
#include "BaseLevel.h"

class InputSystem;

class TitleLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~TitleLevel() = default;

	virtual void Init() override;
	virtual void Update() override;

};

