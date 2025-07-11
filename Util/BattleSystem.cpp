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
#include "../Item/InventoryItem.h"
#include "../Item/BaseItem.h"



bool BattleSystem::ExecuteAttack(BattleCharacter* attacker, BattleCharacter* defender)
{
	if (!attacker || !defender)
	{
		return false;
	}
	attacker->Attack(defender);

	return !defender->IsAlive();
}

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

void BattleSystem::HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser, FBattleResult& result)
{
	Player* player = static_cast<Player*>(winner);
	Monster* monster = static_cast<Monster*>(loser);

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

void BattleSystem::HandleExpReward(BattleCharacter* winner, BattleCharacter* loser, FBattleResult& result)
{
	Player* player = static_cast<Player*>(winner);
	Monster* monster = static_cast<Monster*>(loser);

	int16 expAmount = monster->GetDropExperience();
	bool bPlayerLevelup = player->GainExperience(expAmount);

	result.rewards.expReward = expAmount;
	result.rewards.bLevelUp = bPlayerLevelup;
}

void BattleSystem::HandleGoldReward(BattleCharacter* winner, BattleCharacter* loser, FBattleResult& result)
{
	Player* player = static_cast<Player*>(winner);
	Monster* monster = static_cast<Monster*>(loser);

	int16 goldAmount = monster->GetDropGold();
	player->GainGold(goldAmount);

	result.rewards.goldReward = goldAmount;
}

void BattleSystem::HandleDropItemReward(BattleCharacter* winner, BattleCharacter* loser, FBattleResult& result)
{
	Player* player = static_cast<Player*>(winner);
	Monster* monster = static_cast<Monster*>(loser);
	vector<int32> availableItemIds = ItemDataTable::GetInstance()->GetItemIds();

	if (availableItemIds.empty())
	{
		throw runtime_error("오류 : 전리품 아이템 테이블에 아이템이 존재하지 않습니다.");
	}

	int randomIndex = rand() % availableItemIds.size();
	int32 randomItemId = availableItemIds[randomIndex];

	bool bEquipSuccess = TryEquipOrStoreItem(player, randomItemId, result);

}



bool BattleSystem::TryEquipOrStoreItem(BattleCharacter* winner, int32 droppedItemId, FBattleResult& result)
{
	Player* player = static_cast<Player*>(winner);

	if (!player)
	{
		throw runtime_error("오류: 플레이어를 찾을 수 없습니다.");
	}

	ItemDataTable* itemTable = ItemDataTable::GetInstance();
	EItemType itemType = itemTable->GetItem(droppedItemId)->GetItemType();
	

	if (itemType == EItemType::Weapon || itemType == EItemType::Armor)
	{
		int32 currentEquipId = player->GetEquippedItem(itemType);
		bool bIsBetter = false;

		if (currentEquipId == -1)
		{
			bIsBetter = true;
		}
		else
		{
			const BaseItem* currentEquip = itemTable->GetItem(currentEquipId);
			int32 currentPower = currentEquip->GetItemStatus().GetAttack() + currentEquip->GetItemStatus().GetDefense() + currentEquip->GetItemStatus().GetAgility();
			const BaseItem* newEquip = itemTable->GetItem(droppedItemId);
			int32 newPower = newEquip->GetItemStatus().GetAttack() + newEquip->GetItemStatus().GetDefense() + newEquip->GetItemStatus().GetAgility();

			bIsBetter = (newPower > currentPower);
		}

		if (bIsBetter && player->Equip(droppedItemId))
		{
			if (currentEquipId != -1)
			{
				player->AddItemToInventory(currentEquipId);
			}
			result.rewards.bItemEquipped = true;
			result.rewards.droppedItemId = droppedItemId;
			return true;
		}
	}

	if (player->AddItemToInventory(droppedItemId))
	{
		result.rewards.bItemAddedToInventory = true;
		return true;
	}
	else
	{
		result.rewards.droppedItemId = -1;
		return false;
	}
	return false;
}
