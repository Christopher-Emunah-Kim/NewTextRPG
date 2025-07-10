#include "Equipment.h"
#include "Data/ItemDataTable.h"
#include "../Item/BaseItem.h"
//#include "../Core/GameInstance.h"
//#include "Object/BaseGameObject.h"


Equipment::Equipment()
	:m_weaponItemId(-1), m_armorItemId(-1)
{
}

Equipment::~Equipment()
{
	Release();
}

void Equipment::Release()
{
	m_weaponItemId = -1;
	m_armorItemId = -1;
}

bool Equipment::EquipItem(int32 itemId)
{
	EItemType type = ItemDataTable::GetInstance()->GetItem(itemId)->GetItemType();

	if (type == EItemType::Weapon)
	{
		m_weaponItemId = itemId;
		return true;
	}
	else if (type == EItemType::Armor)
	{
		m_armorItemId = itemId;
		return true;
	}
	
	return false;

	/*if (item)
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
	}*/
}

int32 Equipment::UnequipItem(EItemType itemType)
{
	int32 unequippedItemId = -1;

	if (itemType == EItemType::Weapon)
	{
		unequippedItemId = m_weaponItemId;
		m_weaponItemId = -1;
	}
	else if (itemType == EItemType::Armor)
	{
		unequippedItemId = m_armorItemId;
		m_armorItemId = -1;
	}

	return unequippedItemId;


	/*if (itemType != EItemType::Weapon && itemType != EItemType::Armor)
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

	return unequippedItem;*/
}

int32 Equipment::GetEquippedItem(EItemType itemType) const
{
	if (itemType == EItemType::Weapon)
	{
		return m_weaponItemId;
	}
	
	if (itemType == EItemType::Armor)
	{
		return m_armorItemId;
	}

	return -1;


	/*if (itemType == EItemType::Weapon)
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
	}*/
}


Status Equipment::GetTotalEquipmentStatus() const
{
	Status totalStatus;
	
	if (m_weaponItemId != -1) 
	{
		totalStatus += ItemDataTable::GetInstance()->GetItem(m_weaponItemId)->GetItemStatus();
	}

	if (m_armorItemId != -1)
	{
		totalStatus += ItemDataTable::GetInstance()->GetItem(m_armorItemId)->GetItemStatus();
	}

	/*if (m_weaponSlot)
	{
		totalStatus += m_weaponSlot->GetItemStatus();
	}

	if (m_armorSlot)
	{
		totalStatus += m_armorSlot->GetItemStatus();
	}*/

	return totalStatus;
}