#include "EquipmentComp.h"
#include "PlayerStatusComp.h"
#include "../../Core/GameInstance.h"
#include "../../Object/BaseGameObject.h"


EquipmentComp::EquipmentComp(BaseGameObject* owner)
	: BaseComponent(owner)
{
	m_weaponSlot = nullptr;
	m_armorSlot = nullptr;
}

EquipmentComp::~EquipmentComp()
{
	Release();
}

void EquipmentComp::Release()
{
	m_weaponSlot = nullptr;
	m_armorSlot = nullptr;
}

bool EquipmentComp::EquipItem(BaseItem* item)
{
	if (item)
	{
		EItemType itemType = item->GetItemType();

		if (itemType != EItemType::Weapon && itemType != EItemType::Armor)
		{
			return false;
		}

		BaseItem* existingItem = nullptr;
		if (itemType == EItemType::Weapon && m_weaponSlot != nullptr)
		{
			existingItem = m_weaponSlot;
			// TODO 같은 타입의 장비가 있으면 인벤토리로 이동
		}
		else if (itemType == EItemType::Armor && m_armorSlot != nullptr)
		{
			existingItem = m_armorSlot;
			// TODO 같은 타입의 장비가 있으면 인벤토리로 이동
		}

		if (itemType == EItemType::Weapon)
		{
			m_weaponSlot = item;
		}
		else if (itemType == EItemType::Armor)
		{
			m_armorSlot = item;
		}
		else
		{
			return false;
		}

		GameInstance* gameInstance = GameInstance::GetInstance();
		gameInstance->UpdateEquippedItem(item->GetName(), itemType);

		PlayerStatusComp* statusComp = m_owner->GetComponentsByType<PlayerStatusComp>();
		if (statusComp)
		{
			GameInstance::GetInstance()->UpdatePlayerStatus(statusComp->GetTotalStatus());
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool EquipmentComp::IsEquipped(EItemType itemType) const
{
	if (itemType == EItemType::Weapon)
	{
		return m_weaponSlot != nullptr;
	}
	else if (itemType == EItemType::Armor)
	{
		return m_armorSlot != nullptr;
	}

	return false;
}

BaseItem* EquipmentComp::UnequipItem(EItemType itemType)
{
	if (itemType != EItemType::Weapon && itemType != EItemType::Armor)
	{
		return nullptr;
	}

	if (itemType == EItemType::Weapon && m_weaponSlot == nullptr)
	{
		return nullptr;
	}
	else if (itemType == EItemType::Armor && m_armorSlot == nullptr)
	{
		return nullptr;
	}


	BaseItem* unequippedItem;

	if (itemType == EItemType::Weapon)
	{
		unequippedItem = m_weaponSlot;
		m_weaponSlot = nullptr;
		GameInstance::GetInstance()->UpdateEquippedItem(L"없음", EItemType::Weapon);

	}
	else if (itemType == EItemType::Armor)
	{
		unequippedItem = m_armorSlot;
		m_armorSlot = nullptr;
		GameInstance::GetInstance()->UpdateEquippedItem(L"없음", EItemType::Armor);

	}
	else
	{
		return nullptr; 
	}

	if (unequippedItem)
	{
		PlayerStatusComp* statusComp = m_owner->GetComponentsByType<PlayerStatusComp>();
		if (statusComp)
		{
			GameInstance::GetInstance()->UpdatePlayerStatus(statusComp->GetTotalStatus());
		}
	}

	return unequippedItem;
}

BaseItem* EquipmentComp::GetEquippedItem(EItemType itemType) const
{
	if (itemType == EItemType::Weapon)
	{
		return m_weaponSlot;
	}
	else if (itemType == EItemType::Armor)
	{
		return m_armorSlot;
	}
	else
	{
		return nullptr;
	}
}


Status EquipmentComp::GetTotalEquipmentStatus() const
{
	Status totalStatus;

	if (m_weaponSlot)
	{
		totalStatus += m_weaponSlot->GetItemStatus();
	}

	if (m_armorSlot)
	{
		totalStatus += m_armorSlot->GetItemStatus();
	}

	return totalStatus;
}