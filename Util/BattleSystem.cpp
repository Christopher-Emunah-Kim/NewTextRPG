#include "BattleSystem.h"
#include "../Core/GameInstance.h"
#include "../Object/Character/Player.h"
#include "../Object/Character/Monster.h"
#include "../Level/DungeonLevel.h"
#include "../Core/LevelManager.h"
#include "../Component/Player/PlayerStatusComp.h"
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
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(attacker->GetName() + L"와(과) " + defender->GetName() + L"가(이) 전투를 시작합니다.");
	gameInstance->EnqueueText(L"");

	bool isAttackerTurn = DetermineFirstAttacker(attacker, defender);
	ProcessBattleTurn(attacker, defender, isAttackerTurn);
}


bool BattleSystem::DetermineFirstAttacker(BattleCharacter* attacker, BattleCharacter* defender)
{
	int16 attackerAgility = attacker->GetBattleCharacterInfo().status.GetAgility();
	int16 defenderAgility = defender->GetBattleCharacterInfo().status.GetAgility();

	if (attackerAgility >= defenderAgility)
	{
		GameInstance::GetInstance()->EnqueueText(L"");
		GameInstance::GetInstance()->EnqueueText(attacker->GetName() + L"가(이) 먼저 공격을 시도합니다.");
		GameInstance::GetInstance()->EnqueueText(L"");
		return true;
	}
	else
	{
		GameInstance::GetInstance()->EnqueueText(L"");
		GameInstance::GetInstance()->EnqueueText(defender->GetName() + L"가(이) 먼저 공격을 시도합니다.");
		GameInstance::GetInstance()->EnqueueText(L"");
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
	GameInstance* gameInstance = GameInstance::GetInstance();
	if (!defender->IsAlive())
	{
		gameInstance->EnqueueText(L"");
		gameInstance->EnqueueText(defender->GetName() + L"가 쓰러졌습니다.");
		gameInstance->EnqueueText(L"");
		gameInstance->EnqueueText(L"전투가 종료되었습니다.");
		gameInstance->EnqueueText(L"");
		HandleBattleRewards(attacker, defender);
		return true;
	}
	if (!attacker->IsAlive())
	{
		gameInstance->EnqueueText(L"");
		gameInstance->EnqueueText(attacker->GetName() + L"가 쓰러졌습니다.");
		gameInstance->EnqueueText(L"");
		gameInstance->EnqueueText(L"전투가 종료되었습니다.");
		gameInstance->EnqueueText(L"");
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
		GameInstance* gameInstance = GameInstance::GetInstance();

		PlayerStatusComp* statusComp = player->GetComponentByType<PlayerStatusComp>();
		InventoryComp* inventoryComp = player->GetComponentByType<InventoryComp>();
		EquipmentComp* equipmentComp = player->GetComponentByType<EquipmentComp>();

		if (!statusComp || !inventoryComp || !equipmentComp)
		{
			gameInstance->EnqueueText(L"오류: 플레이어 컴포넌트를 찾을 수 없습니다.");
			return;
		}

		int16 expAmount = monster->GetDropExperience();
		if (statusComp->GainExperience(expAmount))
		{
			gameInstance->EnqueueText(L"경험치 " + to_wstring(expAmount) + L"을(를) 획득했습니다!");
		}

		int16 goldAmount = monster->GetDropGold();
		statusComp->GainGold(goldAmount);
		gameInstance->EnqueueText(L"골드 " + to_wstring(goldAmount) + L"을(를) 획득했습니다!");

		ItemDataTable* itemDataTable = ItemDataTable::GetInstance();
		vector<wstring> availableItems = itemDataTable->GetItemNames();

		if (!availableItems.empty())
		{
			int randomIndex = rand() % availableItems.size();
			wstring randomItemName = availableItems[randomIndex];

			BaseItem* droppedItem = itemDataTable->CreateItem(randomItemName);

			if (droppedItem)
			{
				gameInstance->EnqueueText(L"");
				gameInstance->EnqueueText(monster->GetName() + L"에게서 " + droppedItem->GetName() + L"을(를) 획득했습니다!");

				if (droppedItem->GetItemType() == EItemType::Weapon || droppedItem->GetItemType() == EItemType::Armor)
				{
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

					if (bIsBetter)
					{
						if (equipmentComp->EquipItem(droppedItem))
						{
							gameInstance->EnqueueText(droppedItem->GetName() + L"을(를) 장착했습니다!");

							gameInstance->EnqueueText(L"공격력: +" + to_wstring(droppedItem->GetAttack()) +
								L", 방어력: +" + to_wstring(droppedItem->GetDefense()) +
								L", 민첩성: +" + to_wstring(droppedItem->GetAgility()));
							return; 
						}
					}
				}

				if (inventoryComp->AddItem(droppedItem))
				{
					gameInstance->EnqueueText(droppedItem->GetName() + L"을(를) 인벤토리에 넣었습니다.");
				}
				else
				{
					gameInstance->EnqueueText(L"인벤토리가 가득 차서 " + droppedItem->GetName() + L"을(를) 버렸습니다.");
					delete droppedItem; 
				}
			}
		}
	}
	else if (monster && player && monster->IsAlive() && !player->IsAlive())
	{
		GameInstance::GetInstance()->EnqueueText(L"당신은 " + monster->GetName() + L"에게 패배했습니다!");
	}
}


