#include "Equipment.h"
#include "../Core/GameInstance.h"
#include "Object/BaseGameObject.h"


Equipment::Equipment()
{
	m_weaponSlot = nullptr;
	m_armorSlot = nullptr;
}

Equipment::~Equipment()
{
	Release();
}

void Equipment::Release()
{
	m_weaponSlot = nullptr;
	m_armorSlot = nullptr;
}

bool Equipment::EquipItem(BaseItem* item)
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
		}
		else if (itemType == EItemType::Armor && m_armorSlot != nullptr)
		{
			existingItem = m_armorSlot;
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

		return true;
	}
	else
	{
		return false;
	}
}

BaseItem* Equipment::UnequipItem(EItemType itemType)
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

	}
	else if (itemType == EItemType::Armor)
	{
		unequippedItem = m_armorSlot;
		m_armorSlot = nullptr;

	}
	else
	{
		return nullptr; 
	}

	return unequippedItem;
}

BaseItem* Equipment::GetEquippedItem(EItemType itemType) const
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


Status Equipment::GetTotalEquipmentStatus() const
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