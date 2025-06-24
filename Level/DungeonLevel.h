#pragma once
#include "BaseLevel.h"

class BaseGameObject;

class DungeonLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~DungeonLevel() = default;

private:
	BaseGameObject* m_player = nullptr;

public:
	virtual void Init() override;
	virtual void Update() override;

};

