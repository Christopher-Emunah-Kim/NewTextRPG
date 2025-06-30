#include "BattleSystem.h"
#include "../Core/GameInstance.h"
#include "../Object/Character/Player.h"
#include "../Object/Character/Monster.h"
#include "../Level/DungeonLevel.h"
#include "../Manager/LevelManager.h"


void BattleSystem::StartBattle(BattleCharacter* attacker, BattleCharacter* defender)
{
	if (!attacker || !defender)
	{
		return;
	}

	SetText(L"");
	SetText(attacker->GetName() + L"와(과) " + defender->GetName() + L"가(이) 전투를 시작합니다.");
	SetText(L"");

	bool isAttackerTurn = DetermineFirstAttacker(attacker, defender);
	ProcessBattleTurn(attacker, defender, isAttackerTurn);
}


bool BattleSystem::DetermineFirstAttacker(BattleCharacter* attacker, BattleCharacter* defender)
{
	int16 attackerAgility = attacker->GetBattleCharacterInfo().status.GetAgility();
	int16 defenderAgility = defender->GetBattleCharacterInfo().status.GetAgility();

	if (attackerAgility >= defenderAgility)
	{
		SetText(L"");
		SetText(attacker->GetName() + L"가(이) 먼저 공격을 시도합니다.");
		SetText(L"");
		return true;
	}
	else
	{
		SetText(L"");
		SetText(defender->GetName() + L"가(이) 먼저 공격을 시도합니다.");
		SetText(L"");
		return false;
	}
}

void BattleSystem::ProcessBattleTurn(BattleCharacter* attacker, BattleCharacter* defender, bool isAttackerTurn)
{
	while (attacker->IsAlive() && defender->IsAlive())
	{
		if (isAttackerTurn)
		{
			attacker->Attack(defender);
		}
		else
		{
			defender->Attack(attacker);
		}

		if (CheckBattleEnd(attacker, defender))
		{
			break;
		}

		isAttackerTurn = !isAttackerTurn;
	}
}

bool BattleSystem::CheckBattleEnd(BattleCharacter* attacker, BattleCharacter* defender)
{
	if (!defender->IsAlive())
	{
		SetText(L"");
		SetText(defender->GetName() + L"가 쓰러졌습니다.");
		HandleBattleRewards(attacker, defender);
		SetText(L"");
		SetText(L"전투가 종료되었습니다.");
		SetText(L"");
		return true;
	}
	if (!attacker->IsAlive())
	{
		SetText(L"");
		SetText(attacker->GetName() + L"가 쓰러졌습니다.");
		HandleBattleRewards(defender, attacker);
		SetText(L"");
		SetText(L"전투가 종료되었습니다.");
		SetText(L"");
		return true;
	}
	return false;
}

void BattleSystem::HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser)
{
	Player* player = dynamic_cast<Player*>(winner);
	Monster* monster = dynamic_cast<Monster*>(loser);

	if (player->IsAlive() && !monster->IsAlive())
	{
		// 경험치, 골드, 아이템 등 보상 지급
		// player->GainExperience(monster->GetDropExperience());
		// player->GainGold(monster->GetDropGold());
		monster->DropRewards();
	}
}

void BattleSystem::SetText(const wstring& text)
{
	DungeonLevel* dungeonLevel = dynamic_cast<DungeonLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
	if (dungeonLevel)
	{
		dungeonLevel->AddText(text);
	}
}
