#pragma once
#include "BaseLevel.h"

constexpr __int16 DUNGEON_MAX_MONSTERS = 7;

class Player;
class Monster;
class GameInstance;
class InventoryItem;
struct FBattleRewardInfo;
enum class EPlayerHandleItemResult;

class DungeonLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~DungeonLevel() = default;

	virtual void Init() override;
	virtual void Release() override;

private:
	void SetDungeonStage();
	void ShowDungeonEntranceMenu();
	void MonsterDefeated();
	void ContinueExploration();
	Monster* CreateRandomMonster();

	void ProcessPlayerTurn();
	void ProcessMonsterTurn();
	void ProcessPlayerAttack();
	void ProcessBattleResult(bool monsterDefeated);

	void DisplayVictoryRewards(const FBattleRewardInfo& rewards, Player& player);
	void DisplayDefeatScreen();

	void OnEnterDungeon();
	void OnBackToVillage();
	void OnStartBattle();
	void OnEscape();
	void OnShowUsuableItems();
	void OnUseSelectedItem(int32 itemId);
	void OnTryEscape();

	wstring GetMsgForItemHandleResult(EPlayerHandleItemResult result, const InventoryItem* item);

private:
	GameInstance* gi;
	vector<int32> m_monsterIds;
	Monster* m_currentMonster = nullptr;
	int16 m_activeMonsters = 0;
	int16 m_maxMonsters = DUNGEON_MAX_MONSTERS;

};

