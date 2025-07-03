#pragma once
#include "BaseLevel.h"

constexpr __int16 DUNGEON_MAX_MONSTERS = 7;

class HUD;
class Monster;
struct Status;

class DungeonLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~DungeonLevel() = default;

	virtual void Init() override;
	virtual void Release() override;

private:
	void SetDungeonStage();
	void CreateRandomMonster();
	void Welcome();
	void ContinueExploration();

	void OnEnterStage();
	void OnBackToVillage();
	void OnStartBattle();
	void OnMonsterDefeated();
	void OnEscape();

private:
	vector<wstring> m_monsterNames;
	Monster* m_currentMonster = nullptr;
	int16 m_activeMonseters = 0;
	int16 m_maxMonsters = DUNGEON_MAX_MONSTERS;

};

