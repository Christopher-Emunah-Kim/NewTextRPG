#pragma once
#include "Common.h"

class BattleCharacter;
class InventoryItem;

struct FBattleRewardInfo
{
	int16 expReward = 0; 
	int16 goldReward = 0;
	int32 droppedItemId = -1; 
	bool bLevelUp = false;
	bool bItemEquipped = false;
	bool bItemAddedToInventory = false;
};

struct FBattleResult
{
	BattleCharacter* winner = nullptr;
	BattleCharacter* loser = nullptr;
	FBattleRewardInfo rewards;
};

class BattleSystem
{
private:
	static bool TryEquipOrStoreItem(BattleCharacter* winner, int32 droppedItemId, FBattleResult& result);

public:
	static bool ExecuteAttack(BattleCharacter* attacker, BattleCharacter* defender);
	static bool DetermineFirstAttacker(BattleCharacter* p1, BattleCharacter* p2);
	static bool CanEscape(BattleCharacter* player, BattleCharacter* monster);

	static expected<bool, wstring> HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser, FBattleResult& result);
};