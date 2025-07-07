#pragma once
#include "BaseLevel.h"

constexpr __int16 DUNGEON_MAX_MONSTERS = 7;

class Monster;
class GameInstance;
struct BattleRewardInfo;

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

	void ProcessPlayerTurn();
	void ProcessMonsterTurn();
	void ProcessPlayerAttack();
	void ProcessBattleResult(bool monsterDefeated);

	void DisplayVictoryRewards(const BattleRewardInfo& rewards);
	void DisplayDefeatScreen();

	void OnEnterStage();
	void OnBackToVillage();
	void OnStartBattle();
	void OnMonsterDefeated();
	void OnEscape();
	void OnShowUsuableItems();
	void OnUseSelectedItem(int32 itemId);
	void OnTryEscape();

private:
	GameInstance* gi;
	vector<wstring> m_monsterNames;
	Monster* m_currentMonster = nullptr;
	int16 m_activeMonseters = 0;
	int16 m_maxMonsters = DUNGEON_MAX_MONSTERS;

};

