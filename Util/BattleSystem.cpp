#include "BattleSystem.h"
#include "../Core/GameInstance.h"
#include "../Object/Character/BattleCharacter.h"
#include "../Object/Character/Player.h"
#include "../Object/Character/Monster.h"
#include "../Level/DungeonLevel.h"
#include "../Core/LevelManager.h"
#include "../Component/Equipment.h"
#include "../Component/Inventory.h"
#include "../Data/ItemDataTable.h"



bool BattleSystem::ExecuteAttack(BattleCharacter* attacker, BattleCharacter* defender)
{
	//BattleResult result;
	if (!attacker || !defender)
	{
		return false;
	}
	attacker->Attack(defender);
	Player* player = dynamic_cast<Player*>(attacker);

	if (player)
	{
		GameInstance::GetInstance()->UpdatePlayerHealth(player->GetBattleCharacterInfo().health);
	}

	player = dynamic_cast<Player*>(defender);
	if (player)
	{
		GameInstance::GetInstance()->UpdatePlayerHealth(player->GetBattleCharacterInfo().health);
	}

	return !defender->IsAlive();
}

//BattleResult BattleSystem::ExecuteBattle(BattleCharacter* attacker, BattleCharacter* defender)
//{
//	BattleResult result;
//
//	result.battleMessages.push_back(L"");
//	result.battleMessages.push_back(attacker->GetName() + L"와(과) " + defender->GetName() + L"가(이) 전투를 시작합니다.");
//	result.battleMessages.push_back(L"");
//
//	int16 attackerAgility = attacker->GetBattleCharacterInfo().status.GetAgility();
//	int16 defenderAgility = defender->GetBattleCharacterInfo().status.GetAgility();
//	bool bIsAttackerTurn = (attackerAgility >= defenderAgility);
//
//	if (bIsAttackerTurn)
//	{
//		result.battleMessages.push_back(attacker->GetName() + L"가(이) 먼저 공격을 시도합니다.");
//	}
//	else
//	{
//		result.battleMessages.push_back(defender->GetName() + L"가(이) 먼저 공격을 시도합니다.");
//	}
//
//	ProcessBattleTurn(attacker, defender, bIsAttackerTurn, result);
//
//	if (result.winner)
//	{
//		result.battleMessages.push_back(defender->GetName() + L"가 쓰러졌습니다.");
//		result.battleMessages.push_back(L"전투가 종료되었습니다");
//		result.battleMessages.push_back(L"");
//		HandleBattleRewards(result.winner, result.loser, result);
//	}
//
//	return result;
//}

bool BattleSystem::DetermineFirstAttacker(BattleCharacter* p1, BattleCharacter* p2)
{
	int16 p1Agility = p1->GetBattleCharacterInfo().status.GetAgility();
	int16 p2Agility = p2->GetBattleCharacterInfo().status.GetAgility();

	if (p1Agility >= p2Agility)
	{
		return true; 
	}
	else if (p1Agility < p2Agility)
	{
		return false; 
	}

	return false;
}


void BattleSystem::ProcessBattleTurn(BattleCharacter* p1, BattleCharacter* p2, bool bIsPlayer1Turn, BattleResult& result)
{
	while (p1->IsAlive() && p2->IsAlive())
	{
		BattleCharacter* currentAttacker = nullptr;
		BattleCharacter* currentDefender = nullptr;

		if (bIsPlayer1Turn)
		{
			currentAttacker = p1;
			currentDefender = p2;
		}
		else
		{
			currentAttacker = p2;
			currentDefender = p1;
		}

		currentAttacker->Attack(currentDefender); 

		

		bIsPlayer1Turn = !bIsPlayer1Turn;
	}

	if (p1->IsAlive() && !p2->IsAlive())
	{
		result.winner = p1;
		result.loser = p2;
	}
	else if(!p1->IsAlive() && p2->IsAlive())
	{
		result.winner = p2;
		result.loser = p1;
	}
}

bool BattleSystem::CanEscape(BattleCharacter* player, BattleCharacter* monster)
{
	if (rand() % 3 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BattleSystem::HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result)
{
	Player* player = dynamic_cast<Player*>(winner);
	Monster* monster = dynamic_cast<Monster*>(loser);

	if (player && monster)
	{
		HandleExpReward(player, monster, result);

		HandleGoldReward(player, monster, result);

		HandleDropItemReward(player, monster, result);
	}
	else 
	{
		throw runtime_error("오류: HandleBattleRewards에 플레이어나 몬스터가 존재하지않습니다..");
	}
}



void BattleSystem::HandleExpReward(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result)
{
	Player* player = dynamic_cast<Player*>(winner);
	Monster* monster = dynamic_cast<Monster*>(loser);

	int16 expAmount = monster->GetDropExperience();
	bool bPlayerLevelup = player->GainExperience(expAmount);

	result.rewards.expReward = expAmount;
	result.rewards.bLevelUp = bPlayerLevelup;

	GameInstance::GetInstance()->UpdatePlayerExperience(player->GetExperience());
	if (bPlayerLevelup)
	{
		GameInstance::GetInstance()->UpdatePlayerLevel(player->GetBattleCharacterInfo().characterLevel);
	}
}

void BattleSystem::HandleGoldReward(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result)
{
	Player* player = dynamic_cast<Player*>(winner);
	Monster* monster = dynamic_cast<Monster*>(loser);

	int16 goldAmount = monster->GetDropGold();
	player->GainGold(goldAmount);

	result.rewards.goldReward = goldAmount;
	GameInstance::GetInstance()->UpdatePlayerGold(player->GetGold());
}

void BattleSystem::HandleDropItemReward(BattleCharacter* winner, BattleCharacter* loser, BattleResult& result)
{
	Player* player = dynamic_cast<Player*>(winner);
	Monster* monster = dynamic_cast<Monster*>(loser);
	ItemDataTable* itemDataTable = ItemDataTable::GetInstance();
	vector<int32> availableItemIds = itemDataTable->GetItemIds();

	if (availableItemIds.empty())
	{
		throw runtime_error("오류 : 전리품 아이템 테이블에 아이템이 존재하지 않습니다.");
	}

	
	int randomIndex = rand() % availableItemIds.size();
	int32 randomItemId = availableItemIds[randomIndex];
	const BaseItem* templateItem = itemDataTable->GetItem(randomItemId);

	if (!templateItem)
	{
		throw runtime_error("오류: 전리품 templateItem이 존재하지 않습니다.");
	}

	BaseItem* droppedItem = templateItem->CreateItem();
	if (!droppedItem)
	{
		throw runtime_error("오류: droppedItem이 존재하지 않습니다.");
	}


	droppedItem->AddItemCount(1);
	result.rewards.droppedItem = droppedItem;

	TryEquipOrStoreItem(player, droppedItem, result);

}



bool BattleSystem::TryEquipOrStoreItem(BattleCharacter* winner, BaseItem* droppedItem, BattleResult& result)
{
	Player* player = dynamic_cast<Player*>(winner);

	if (!player)
	{
		throw runtime_error("오류: 플레이어를 찾을 수 없습니다.");
	}

    Equipment& playerEquipment = player->GetEquipment();
	Inventory& playerInventory = player->GetInventory();

	if (droppedItem->GetItemType() != EItemType::Weapon && droppedItem->GetItemType() != EItemType::Armor)
	{
		return false;
	}

	BaseItem* currentEquip = playerEquipment.GetEquippedItem(droppedItem->GetItemType());
	bool bIsBetter = false;

	if (!currentEquip)
	{
		bIsBetter = true;
	}
	else
	{
		int32 currentPower = currentEquip->GetAttack() + currentEquip->GetDefense() + currentEquip->GetAgility();
		int32 newPower = droppedItem->GetAttack() + droppedItem->GetDefense() + droppedItem->GetAgility();
		bIsBetter = (newPower > currentPower);
	}


	if (bIsBetter && playerEquipment.EquipItem(droppedItem))
	{
		result.rewards.bItemEquipped = true;
		return true;
	}


	if (playerInventory.AddItem(droppedItem))
	{
		result.rewards.bItemAddedToInventory = true;
	}
	else
	{
		delete droppedItem;
		result.rewards.droppedItem = nullptr;
	}


	return false;
}
