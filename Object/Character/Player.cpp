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
	SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	InitializeComponents();

	BattleCharacter::Init();
}


void Player::InitializeComponents()
{
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

	PlayerStatusComp* statusComp = GetComponentsByType<PlayerStatusComp>();
	if (statusComp)
	{
		const FPlayerInfo& info = statusComp->GetPlayerInfo();
		gameInstance->UpdatePlayerName(GetTag());
		gameInstance->UpdatePlayerLevel(info.characterLevel);
		gameInstance->UpdatePlayerHealth(info.health, info.maxHealth);
		gameInstance->UpdatePlayerStatus(statusComp->GetTotalStatus());
	}

	EquipmentComp* equipComp = GetComponentsByType<EquipmentComp>();
	if (equipComp)
	{
		BaseItem* weapon = equipComp->GetEquippedItem(EItemType::Weapon);
		BaseItem* armor = equipComp->GetEquippedItem(EItemType::Armor);

		gameInstance->UpdateEquippedItem(weapon ? weapon->GetName() : L"없음", EItemType::Weapon);
		gameInstance->UpdateEquippedItem(armor ? armor->GetName() : L"없음", EItemType::Armor);
	}

	InventoryComp* invComp = GetComponentsByType<InventoryComp>();
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
		if (GetLevel() == level)
		{
			return;
		}

		if (GetLevel() != nullptr)
		{
			GetLevel()->DetachObject(this);
		}

		SetLevelArea(level);

		if (IsComponentsEmpty())
		{
			Init();
		}

		if (level->FindObject(L"Player") == nullptr)
		{
			level->AddObject(this);
		}
	}
}



