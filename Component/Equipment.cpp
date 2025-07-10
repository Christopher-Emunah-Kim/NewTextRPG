#include "Equipment.h"
#include "Data/ItemDataTable.h"
#include "../Item/BaseItem.h"


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

	return totalStatus;
}