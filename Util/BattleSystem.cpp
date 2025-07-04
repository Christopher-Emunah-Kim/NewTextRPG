#include "BattleSystem.h"
#include "../Core/GameInstance.h"
#include "../Object/Character/BattleCharacter.h"
#include "../Object/Character/Player.h"
#include "../Object/Character/Monster.h"
#include "../Level/DungeonLevel.h"
#include "../Core/LevelManager.h"
#include "../Component/Player/EquipmentComp.h"
#include "../Component/Player/InventoryComp.h"
#include "../Data/ItemDataTable.h"



void BattleSystem::StartBattle(BattleCharacter* attacker, BattleCharacter* defender)
{
	if (!attacker || !defender)
	{
		return;
	}
	GameInstance* gameInstance = GameInstance::GetInstance();
	gameInstance->WriteLine(L"");
	gameInstance->WriteLine(attacker->GetName() + L"와(과) " + defender->GetName() + L"가(이) 전투를 시작합니다.");
	gameInstance->WriteLine(L"");

	bool isAttackerTurn = DetermineFirstAttacker(attacker, defender);
	ProcessBattleTurn(attacker, defender, isAttackerTurn);
}


bool BattleSystem::DetermineFirstAttacker(BattleCharacter* attacker, BattleCharacter* defender)
{
	int16 attackerAgility = attacker->GetBattleCharacterInfo().status.GetAgility();
	int16 defenderAgility = defender->GetBattleCharacterInfo().status.GetAgility();

	if (attackerAgility >= defenderAgility)
	{
		GameInstance::GetInstance()->WriteLine(L"");
		GameInstance::GetInstance()->WriteLine(attacker->GetName() + L"가(이) 먼저 공격을 시도합니다.");
		GameInstance::GetInstance()->WriteLine(L"");
		return true;
	}
	else
	{
		GameInstance::GetInstance()->WriteLine(L"");
		GameInstance::GetInstance()->WriteLine(defender->GetName() + L"가(이) 먼저 공격을 시도합니다.");
		GameInstance::GetInstance()->WriteLine(L"");
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

		Player* playerAttacker = dynamic_cast<Player*>(attacker);
		if (playerAttacker)
		{
			GameInstance::GetInstance()->UpdatePlayerHealth(playerAttacker->GetBattleCharacterInfo().health);
		}

		Player* playerDefender = dynamic_cast<Player*>(defender);
		if (playerDefender)
		{
			GameInstance::GetInstance()->UpdatePlayerHealth(playerDefender->GetBattleCharacterInfo().health);
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
	GameInstance* gameInstance = GameInstance::GetInstance();
	if (!defender->IsAlive())
	{
		gameInstance->WriteLine(L"");
		gameInstance->WriteLine(defender->GetName() + L"가 쓰러졌습니다.");
		gameInstance->WriteLine(L"");
		gameInstance->WriteLine(L"전투가 종료되었습니다.");
		gameInstance->WriteLine(L"");
		HandleBattleRewards(attacker, defender);
		return true;
	}
	if (!attacker->IsAlive())
	{
		gameInstance->WriteLine(L"");
		gameInstance->WriteLine(attacker->GetName() + L"가 쓰러졌습니다.");
		gameInstance->WriteLine(L"");
		gameInstance->WriteLine(L"전투가 종료되었습니다.");
		gameInstance->WriteLine(L"");
		HandleBattleRewards(defender, attacker);
		return true;
	}
	return false;
}

void BattleSystem::HandleBattleRewards(BattleCharacter* winner, BattleCharacter* loser)
{
	Player* player = dynamic_cast<Player*>(winner);
	Monster* monster = dynamic_cast<Monster*>(loser);

	if (player && monster && player->IsAlive() && !monster->IsAlive())
	{
		HandlePlayerVictory(player, monster);
		return;
	}
	else if (monster && player && monster->IsAlive() && !player->IsAlive())
	{
		GameInstance::GetInstance()->WriteLine(L"당신은 " + monster->GetName() + L"에게 패배했습니다!");
	}
}


void BattleSystem::HandlePlayerVictory(BattleCharacter* player, BattleCharacter* monster)
{
	HandleExpReward(player, monster);

	HandleGoldReward(player, monster);

	HandleDropItemReward(player, monster);
}


void BattleSystem::HandleExpReward(BattleCharacter* winner, BattleCharacter* loser)
{
	Player* player = dynamic_cast<Player*>(winner);
	Monster* monster = dynamic_cast<Monster*>(loser);
	GameInstance* gameInstance = GameInstance::GetInstance();

	int16 expAmount = monster->GetDropExperience();
	bool bPlayerLevelup = player->GainExperience(expAmount);
	gameInstance->WriteLine(L"경험치 " + to_wstring(expAmount) + L"을(를) 획득했습니다!");
	gameInstance->UpdatePlayerExperience(player->GetExperience());
	if (bPlayerLevelup)
	{
		gameInstance->WriteLine(L"레벨업! 능력치가 상승합니다.");
		gameInstance->UpdatePlayerLevel(player->GetBattleCharacterInfo().characterLevel);
	}
}

void BattleSystem::HandleGoldReward(BattleCharacter* winner, BattleCharacter* loser)
{
	Player* player = dynamic_cast<Player*>(winner);
	Monster* monster = dynamic_cast<Monster*>(loser);
	GameInstance* gameInstance = GameInstance::GetInstance();

	int16 goldAmount = monster->GetDropGold();
	player->GainGold(goldAmount);
	gameInstance->WriteLine(L"골드 " + to_wstring(goldAmount) + L"을(를) 획득했습니다!");
	gameInstance->UpdatePlayerGold(player->GetGold());
}

void BattleSystem::HandleDropItemReward(BattleCharacter* winner, BattleCharacter* loser)
{
	Player* player = dynamic_cast<Player*>(winner);
	Monster* monster = dynamic_cast<Monster*>(loser);
	GameInstance* gameInstance = GameInstance::GetInstance();
	ItemDataTable* itemDataTable = ItemDataTable::GetInstance();

	vector<int32> availableItemIds = itemDataTable->GetItemIds();

	InventoryComp* inventoryComp = player->GetComponentByType<InventoryComp>();
	EquipmentComp* equipmentComp = player->GetComponentByType<EquipmentComp>();

	if (!inventoryComp || !equipmentComp)
	{
		gameInstance->WriteLine(L"오류: 플레이어 컴포넌트를 찾을 수 없습니다.");
		return;
	}

	if (availableItemIds.empty())
	{
		gameInstance->WriteLine(L"오류: 아이템테이블에 아이템이 존재하지 않습니다.");
		return;
	}

	srand(static_cast<unsigned int>(time(nullptr)));
	int randomIndex = rand() % availableItemIds.size();
	int32 randomItemId = availableItemIds[randomIndex];
	const BaseItem* templateItem = itemDataTable->GetItem(randomItemId);

	if (!templateItem)
	{
		gameInstance->WriteLine(L"오류: templateItem이 존재하지 않습니다.");
		return;
	}

	BaseItem* droppedItem = templateItem->CreateItem();
	if (!droppedItem)
	{
		gameInstance->WriteLine(L"오류: droppedItem이 존재하지 않습니다.");
		return;
	}

	droppedItem->AddItemCount(1);
	gameInstance->WriteLine(L"");
	wstring monsterName = monster->GetName();
	wstring itemName = droppedItem->GetName();
	gameInstance->WriteLine(monsterName + L"에게서 " + itemName + L"을(를) 획득했습니다!");


	if (CheckEquippable(player, droppedItem))
	{
		return;
	}
	
	AddItemToInventory(player, droppedItem);

}



bool BattleSystem::CheckEquippable(BattleCharacter* winner, BaseItem* droppedItem)
{
	Player* player = dynamic_cast<Player*>(winner);
	GameInstance* gameInstance = GameInstance::GetInstance();
	EquipmentComp* equipmentComp = player->GetComponentByType<EquipmentComp>();

	if (droppedItem->GetItemType() != EItemType::Weapon && droppedItem->GetItemType() != EItemType::Armor)
	{
		return false;
	}

	BaseItem* currentEquip = equipmentComp->GetEquippedItem(droppedItem->GetItemType());
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


	if (bIsBetter && equipmentComp->EquipItem(droppedItem))
	{
		gameInstance->WriteLine(droppedItem->GetName() + L"을(를) 장착했습니다!");

		gameInstance->WriteLine(L"공격력: +" + to_wstring(droppedItem->GetAttack()) +
			L", 방어력: +" + to_wstring(droppedItem->GetDefense()) +
			L", 민첩성: +" + to_wstring(droppedItem->GetAgility()));
		
		return true;
	}

	return false;
}


void BattleSystem::AddItemToInventory(BattleCharacter* winner, BaseItem* droppedItem)
{
	Player* player = dynamic_cast<Player*>(winner);
	GameInstance* gameInstance = GameInstance::GetInstance();
	InventoryComp* inventoryComp = player->GetComponentByType<InventoryComp>();

	if (inventoryComp->AddItem(droppedItem))
	{
		gameInstance->WriteLine(droppedItem->GetName() + L"을(를) 인벤토리에 넣었습니다.");
	}
	else
	{
		gameInstance->WriteLine(L"인벤토리가 가득 차서 " + droppedItem->GetName() + L"을(를) 버렸습니다.");
		delete droppedItem;
	}
}