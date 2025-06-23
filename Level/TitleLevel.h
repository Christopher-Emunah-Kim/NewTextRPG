#pragma once
#include "BaseLevel.h"

class InputSystem;
class Player;

class TitleLevel final : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~TitleLevel() = default;

private:
	Player* m_player = nullptr;

public:
	virtual void Init() override;
	virtual void Update() override;

};

