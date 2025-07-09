#include "Player.h"
#include "../../Screen.h"
#include "../../Core/GameInstance.h"
#include "../../Level/BaseLevel.h"
#include "../../Data/ItemDataTable.h"


Player::Player()
	:BattleCharacter(nullptr, L"최강워로드"), m_gold(DEFAULT_OWNED_GOLD),
	m_experience(0, PlayerLevelPropertiesTable::GetInstance()->GetRequiredMaxExp(DEFAULT_LEVEL)),
	m_inventory(), m_equipment()
{ 
	m_battleCharacterInfo.description = L"스칼드로서의 삶에 회한을 느낀 전사";
}

void Player::Init()
{
	UpdatePlayerHUD();

	BattleCharacter::Init();
}

void Player::UpdatePlayerHUD()
{
	GameInstance* gameInstance = GameInstance::GetInstance();

	gameInstance->UpdatePlayerName(GetTag());
	gameInstance->UpdatePlayerLevel(m_battleCharacterInfo.characterLevel);
	gameInstance->UpdatePlayerHealth(m_battleCharacterInfo.health);
	gameInstance->UpdatePlayerStatus(GetTotalPlayerStatus());
	gameInstance->UpdatePlayerExperience(m_experience);
	gameInstance->UpdatePlayerGold(m_gold);

	BaseItem* weapon = m_equipment.GetEquippedItem(EItemType::Weapon);
	BaseItem* armor = m_equipment.GetEquippedItem(EItemType::Armor);

	if (weapon)
	{
		gameInstance->UpdateEquippedItem(weapon->GetName(), EItemType::Weapon);
	}
	else
	{
		gameInstance->UpdateEquippedItem(L"없음", EItemType::Weapon);
	}

	if (armor)
	{
		gameInstance->UpdateEquippedItem(armor->GetName(), EItemType::Armor);
	}
	else
	{
		gameInstance->UpdateEquippedItem(L"없음", EItemType::Armor);
	}

	const vector<BaseItem*>& items = m_inventory.GetInventoryItems();
	for (size_t i = 0; i < items.size(); ++i)
	{
		BaseItem* item = items[i];
		gameInstance->UpdateInvetoryItems(m_inventory.GetInventoryItems());
	}
}

void Player::LoadLevelPropertiesByLevel()
{
	FLevelProperties levelProps = PlayerLevelPropertiesTable::GetInstance()->LoadPlayerLevelData(m_battleCharacterInfo.characterLevel);

	m_battleCharacterInfo.health = Health::New(levelProps.maxHealthPerLevel);
	m_experience.SetMaxExp(levelProps.maxExperiencePerLevel);

	m_battleCharacterInfo.status = Status(
		levelProps.attackPerLevel,
		levelProps.defensePerLevel,
		levelProps.agilityPerLevel
	);
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

		level->AddObject(this);
	}
	else
	{
		GameInstance::GetInstance()->WriteLine(L"[오류] 플레이어를 등록할 레벨이 존재하지 않습니다.");
		SetLevelArea(GetLevel());
	}
}

Health Player::GetHealthForHUD() const
{
	return m_battleCharacterInfo.health;
}

int32 Player::GetGoldAmount() const
{
	return m_gold.GetAmount();
}

bool Player::CanAfford(int32 cost) const
{
	return m_gold.CanAfford(cost);
}

bool Player::IsFullHealth() const
{
	return m_battleCharacterInfo.health.IsFull();
}

void Player::Recover(int32 amount)
{
	m_battleCharacterInfo.health = m_battleCharacterInfo.health.Recover(amount);
}

int32 Player::GetCurrentHealth() const
{
	return m_battleCharacterInfo.health.GetCurrentAmount();
}

int32 Player::GetMaxHealth() const
{
	return m_battleCharacterInfo.health.GetMaxAmount();
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

Gold Player::GetGoldForHUD() const
{
	return m_gold;
}

bool Player::GainExperience(int32 exp)
{
	int16 levelUpCount = m_experience.AddExperience(exp, m_battleCharacterInfo.characterLevel);

	GameInstance::GetInstance()->UpdatePlayerExperience(m_experience);

	if (levelUpCount > 0)
	{
		m_battleCharacterInfo.characterLevel += levelUpCount;

		LoadLevelPropertiesByLevel();

		GameInstance::GetInstance()->UpdatePlayerLevel(m_battleCharacterInfo.characterLevel);
		GameInstance::GetInstance()->UpdatePlayerHealth(m_battleCharacterInfo.health);
		GameInstance::GetInstance()->UpdatePlayerStatus(GetTotalPlayerStatus());

		return true;
	}

	return false;
}

const vector<BaseItem*> Player::GetInventoryItems() const 
{
	return m_inventory.GetInventoryItems();
}

void Player::RemoveItemFromInventory(int32 itemId, int16 count)
{
	m_inventory.RemoveItem(itemId, count);
}

bool Player::AddItemToInventory(BaseItem* item)
{
	return m_inventory.AddItem(item);
}

BaseItem* Player::GetItemFromInventory(int32 itemId) const
{
	return m_inventory.GetItem(itemId);
}

EPlayerHandleItemResult Player::HandlePurchasedItem(BaseItem* item)
{
	if (item == nullptr)
	{
		return EPlayerHandleItemResult::ItemNullPtr;
	}

	EItemType itemType = item->GetItemType();
	bool bIsEquippable = ItemDataTable::GetInstance()->IsEquippable(item->GetItemID());

	if (bIsEquippable)
	{
		bool bIsAlreadyEquipped = false;
		if((m_equipment.GetEquippedItem(EItemType::Weapon) != nullptr && EItemType::Weapon == itemType)|| 
		   (m_equipment.GetEquippedItem(EItemType::Armor) != nullptr && EItemType::Armor == itemType))
		{
			bIsAlreadyEquipped = true;
		}

		if (bIsAlreadyEquipped)
		{
			item->AddItemCount(1);
			if (AddItemToInventory(item))
			{
				return EPlayerHandleItemResult::AddToInventory;
			}

			delete item;
			return EPlayerHandleItemResult::InventoryFull;
		}
		else
		{
			Equip(item);
			return EPlayerHandleItemResult::Equipped;
		}
	}
	else
	{
		item->AddItemCount(1);
		if (AddItemToInventory(item))
		{
			return EPlayerHandleItemResult::AddToInventory;
		}
		
		delete item;
		return EPlayerHandleItemResult::InventoryFull;
	}
}

EPlayerHandleItemResult Player::HandleOwnedItem(BaseItem* item)
{
	if (item == nullptr)
	{
		return EPlayerHandleItemResult::ItemNullPtr;
	}

	EItemType itemType = item->GetItemType();

	switch (itemType)
	{
	case EItemType::Weapon:
	case EItemType::Armor:
	{
		if (Equip(item))
		{
			return EPlayerHandleItemResult::Equipped;
		}
		else
		{
			return EPlayerHandleItemResult::NotUsuableItem;
		}
	}
	case EItemType::Consumable:
	{
		Recover(20);
		return EPlayerHandleItemResult::UseItem;
	}
	break;
	
	default:
	{
		return EPlayerHandleItemResult::NotUsuableItem;
	}
	break;
	}
}


bool Player::Equip(BaseItem* item)
{
	return m_equipment.EquipItem(item);
}

BaseItem* Player::GetEquippedItem(EItemType itemType) const
{
	return m_equipment.GetEquippedItem(itemType);
}

Status Player::GetTotalPlayerStatus() const
{
	Status baseStatus = m_battleCharacterInfo.status;
	Status equipStatus = m_equipment.GetTotalEquipmentStatus();
	baseStatus = Status::AddStatus(baseStatus, equipStatus);

	return baseStatus;
}

Experience Player::GetExperienceForHUD() const
{
	return m_experience;
}


