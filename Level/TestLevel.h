#pragma once
#include "BaseLevel.h"

constexpr int32 LEVEL_TRANSITION_POSITION_X = 30;
constexpr int32 LEVEL_TRANSITION_POSITION_Y = 20;
constexpr int32 TRANSITION_AREA_RADIUS = 3;

class TestLevel final : public BaseLevel
{
public:
	TestLevel(const string& tag) : BaseLevel(tag) { }
	virtual ~TestLevel() = default;

private:
	bool m_playerInTransitionArea = false;
	bool m_diplayedTransitionMessage = false;

private:
	void CheckPlayerInTransitionArea();

public:
	virtual void Init() override;
	virtual void Update() override;

};

