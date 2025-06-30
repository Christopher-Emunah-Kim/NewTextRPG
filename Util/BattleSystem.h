#pragma once
#include "../Object/Character/BattleCharacter.h"

class BattleSystem
{
public:
	static void StartBattle(BattleCharacter* attacker, BattleCharacter* defender);

private:
	static bool DetermineFirstAttacker(BattleCharacter* attacker, BattleCharacter* defender);
	static void ProcessBattleTurn(BattleCharacter* attacker, BattleCharacter* defender, bool isAttackerTurn);
	static bool CheckBattleEnd(BattleCharacter* attacker, BattleCharacter* defender);
	static void HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser);
	static void SetText(const wstring& text);
};