#include "Player.h"
#include "../../Screen.h"
#include "../../Core/GameInstance.h"
#include "../../Level/BaseLevel.h"
#include "../../Component/Player/EquipmentComp.h"
#include "../../Component/Player/PlayerStatusComp.h"
#include "../../Component/Player/InventoryComp.h"


Player::Player()
	:BattleCharacter(nullptr, L"Player"), m_playerInfo(DEFAULT_LEVEL)
{
}


void Player::Init()
{
	InitializeComponents();

	BattleCharacter::Init();
}


void Player::InitializeComponents()
{
	//debug
	//GameInstance::GetInstance()->EnqueueText(L"InitializeComponents 호출");


	if (false == HasComponentType<PlayerStatusComp>())
	{
		AddComponent(new PlayerStatusComp(this));
	}
	if (false == HasComponentType<InventoryComp>())
	{
		AddComponent(new InventoryComp(this));
	}

	if (false == HasComponentType<EquipmentComp>())
	{
		AddComponent(new EquipmentComp(this));
	}

	GameInstance* gameInstance = GameInstance::GetInstance();

	PlayerStatusComp* statusComp = GetComponentByType<PlayerStatusComp>();
	if (statusComp)
	{
		const FPlayerInfo& info = statusComp->GetPlayerInfo();
		gameInstance->UpdatePlayerName(GetTag());
		gameInstance->UpdatePlayerLevel(info.characterLevel);
		gameInstance->UpdatePlayerHealth(info.health, info.maxHealth);
		gameInstance->UpdatePlayerStatus(statusComp->GetTotalStatus());
	}

	EquipmentComp* equipComp = GetComponentByType<EquipmentComp>();
	if (equipComp)
	{
		BaseItem* weapon = equipComp->GetEquippedItem(EItemType::Weapon);
		BaseItem* armor = equipComp->GetEquippedItem(EItemType::Armor);

		gameInstance->UpdateEquippedItem(weapon ? weapon->GetName() : L"없음", EItemType::Weapon);
		gameInstance->UpdateEquippedItem(armor ? armor->GetName() : L"없음", EItemType::Armor);
	}

	InventoryComp* invComp = GetComponentByType<InventoryComp>();
	if (invComp)
	{
		const vector<BaseItem*>& items = invComp->GetInventoryItems();
		for (size_t i = 0; i < items.size(); ++i)
		{
			BaseItem* item = items[i];
			gameInstance->UpdateInvetoryItems(item->GetName());
		}
	}
}

void Player::RegisterNewLevelArea(BaseLevel* level)
{
	if (level != nullptr)
	{
		//debug
		//GameInstance::GetInstance()->EnqueueText(L"RegisterNewLevelArea 호출: " + level->GetTag());
		//GameInstance::GetInstance()->EnqueueText(L"컴포넌트 상태: " + std::to_wstring(IsComponentsEmpty()));


		if (GetLevel() == level)
		{
			return;
		}

		if (GetLevel() != nullptr)
		{
			GetLevel()->DetachObject(this);
		}

		SetLevelArea(level);

		if (level->FindObject(L"Player") == nullptr)
		{
			level->AddObject(this);
		}

		if (IsComponentsEmpty())
		{
			Init();
		}
		else
		{
			InitializeComponents();
		}

		
	}
}



