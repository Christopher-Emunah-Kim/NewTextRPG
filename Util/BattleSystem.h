#pragma once
#include "Common.h"

class BattleCharacter;
class BaseItem;

struct BattleRewardInfo
{
	int16 expReward = 0; 
	int16 goldReward = 0;
	bool bLevelUp = false;
	BaseItem* droppedItem = nullptr; 
	bool bItemEquipped = false;
	bool bItemAddedToInventory = false;
};

struct BattleResult
{
	BattleCharacter* winner = nullptr;
	BattleCharacter* loser = nullptr;
	vector<wstring> battleMessages;
	BattleRewardInfo rewards;
};

class BattleSystem
{
private:
	static void ProcessBattleTurn(BattleCharacter* p1, BattleCharacter* p2, bool bIsPlayer1Turn, BattleResult& result);
	static void HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result);

	static void HandleExpReward(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result);
	static void HandleGoldReward(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result);
	static void HandleDropItemReward(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result);
	static bool TryEquipOrStoreItem(BattleCharacter* winner, BaseItem* droppedItem, BattleResult& result);

public:
	static BattleResult ExecuteBattle(BattleCharacter* attacker, BattleCharacter* defender);
};