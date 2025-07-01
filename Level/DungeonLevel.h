#pragma once
#include "BaseLevel.h"


class HUD;
class Monster;
struct Status;

class DungeonLevel : public BaseLevel
{

public:
	using BaseLevel::BaseLevel;
	virtual ~DungeonLevel() = default;

private:
	Monster* m_monster = nullptr;


public:
	virtual void Init() override;
	virtual void Release() override;

private:
	void SetDungeonStage();
	void Welcome();

	void OnEnterStage();
	void OnBackToVillage();
	void OnStartBattle();
	void OnEscape();
};

