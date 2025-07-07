#pragma once
#include "Common.h"

class BattleCharacter;
class BaseItem;

struct BattleRewardInfo
{
	int16 expReward = 0; 
	int16 goldReward = 0;
	bool bLevelUp = false;
	bool bItemEquipped = false;
	bool bItemAddedToInventory = false;
	BaseItem* droppedItem = nullptr; 
};

struct BattleResult
{
	BattleCharacter* winner = nullptr;
	BattleCharacter* loser = nullptr;
	BattleRewardInfo rewards;
	vector<wstring> battleMessages;
};

class BattleSystem
{
private:
	static void HandleExpReward(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result);
	static void HandleGoldReward(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result);
	static void HandleDropItemReward(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result);
	static bool TryEquipOrStoreItem(BattleCharacter* winner, BaseItem* droppedItem, BattleResult& result);

public:
	static bool ExecuteAttack(BattleCharacter* attacker, BattleCharacter* defender);
	static bool DetermineFirstAttacker(BattleCharacter* p1, BattleCharacter* p2);
	static bool CanEscape(BattleCharacter* player, BattleCharacter* monster);
	static void HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result);
};