#pragma once
#include "BaseLevel.h"

class BaseGameObject;

class TitleLevel final : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~TitleLevel() = default;

private:
	BaseGameObject* m_player = nullptr;

public:
	virtual void Init() override;
	virtual void Update() override;

};

