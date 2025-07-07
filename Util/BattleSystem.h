#pragma once
#include "Common.h"

class BattleCharacter;
class BaseItem;

struct FBattleRewardInfo
{
	int16 expReward = 0; 
	int16 goldReward = 0;
	bool bLevelUp = false;
	bool bItemEquipped = false;
	bool bItemAddedToInventory = false;
	BaseItem* droppedItem = nullptr; 
};

struct FBattleResult
{
	BattleCharacter* winner = nullptr;
	BattleCharacter* loser = nullptr;
	FBattleRewardInfo rewards;
	//vector<wstring> battleMessages;
};

class BattleSystem
{
private:
	static void HandleExpReward(BattleCharacter* winner, BattleCharacter* loser, FBattleResult& result);
	static void HandleGoldReward(BattleCharacter* winner, BattleCharacter* loser, FBattleResult& result);
	static void HandleDropItemReward(BattleCharacter* winner, BattleCharacter* loser, FBattleResult& result);
	static bool TryEquipOrStoreItem(BattleCharacter* winner, BaseItem* droppedItem, FBattleResult& result);

public:
	static bool ExecuteAttack(BattleCharacter* attacker, BattleCharacter* defender);
	static bool DetermineFirstAttacker(BattleCharacter* p1, BattleCharacter* p2);
	static bool CanEscape(BattleCharacter* player, BattleCharacter* monster);
	static void HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser, FBattleResult& result);
};