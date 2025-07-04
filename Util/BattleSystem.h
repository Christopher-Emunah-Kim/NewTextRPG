#pragma once

class BattleCharacter;
class BaseItem;

class BattleSystem
{

private:
	static bool DetermineFirstAttacker(BattleCharacter* attacker, BattleCharacter* defender);
	static void ProcessBattleTurn(BattleCharacter* attacker, BattleCharacter* defender, bool isAttackerTurn);
	static bool CheckBattleEnd(BattleCharacter* attacker, BattleCharacter* defender);
	static void HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser);

	static void HandlePlayerVictory(BattleCharacter* player, BattleCharacter* monster);
	static void HandleExpReward(BattleCharacter* winner, BattleCharacter* loser);
	static void HandleGoldReward(BattleCharacter* winner, BattleCharacter* loser);
	static void HandleDropItemReward(BattleCharacter* winner, BattleCharacter* loser);
	static bool CheckEquippable(BattleCharacter* winner, BaseItem* droppedItem);
	static void AddItemToInventory(BattleCharacter* winner, BaseItem* droppedItem);

public:
	static void StartBattle(BattleCharacter* attacker, BattleCharacter* defender);
};