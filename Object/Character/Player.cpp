#include "Player.h"
#include "../../Screen.h"
#include "../../Core/GameInstance.h"
#include "../../Level/BaseLevel.h"
#include "../../Component/Player/EquipmentComp.h"
#include "../../Component/Player/PlayerStatusComp.h"
#include "../../Component/Player/InventoryComp.h"


Player::Player()
	:BattleCharacter(nullptr, L"Player"), m_playerInfo(DEFAULT_LEVEL), m_gold(DEFAULT_OWNED_GOLD)
{
}


void Player::Init()
{
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

	PlayerStatusComp* statusComp = GetComponentByType<PlayerStatusComp>();
	if (statusComp)
	{
		const FPlayerInfo& info = statusComp->GetPlayerInfo();
		gameInstance->UpdatePlayerName(GetTag());
		gameInstance->UpdatePlayerLevel(info.characterLevel);
		gameInstance->UpdatePlayerHealth(info.health);
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
		if (GetLevel() == level)
		{
			return;
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


void Player::TakeDamage(int32 amount)
{
	m_playerInfo.health = m_playerInfo.health.TakeDamage(amount);
}

Health Player::GetHealth() const
{
	return m_playerInfo.health;
}

bool Player::CanAfford(int32 cost) const
{
	return m_gold.CanAfford(cost);
}

bool Player::IsFullHealth() const
{
	return m_playerInfo.health.IsFull();
}

void Player::Recover(int32 amount)
{
	m_playerInfo.health = m_playerInfo.health.Recover(amount);
}

bool Player::UseGold(int32 amount)
{
	m_gold = m_gold.Use(amount);

	if (m_gold.GetAmount() > 0)
	{
		return true;
	}

	return false;
}

void Player::GainGold(int32 amount)
{
	m_gold = m_gold.Gain(amount);
}

Gold Player::GetGold() const
{
	return m_gold;
}

int32 Player::GetGoldAmount() const
{
	return m_gold.GetAmount();
}

