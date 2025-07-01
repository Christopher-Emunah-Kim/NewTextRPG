#include "EquipmentComp.h"
#include "PlayerStatusComp.h"
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

		if (m_weaponSlot != nullptr || m_armorSlot != nullptr)
		{
			// TODO 같은 타입의 장비가 있으면 인벤토리로 이동
			//return false;
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

		PlayerStatusComp* statusComp = m_owner->GetComponentsByType<PlayerStatusComp>();
		if (statusComp)
		{
			Status currentStatus = statusComp->GetPlayerInfo().status;
			Status itemStatus = item->GetItemStatus();
			statusComp->GetPlayerInfo().status.AddStatus(currentStatus, itemStatus);
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

	PlayerStatusComp* statusComp = m_owner->GetComponentsByType<PlayerStatusComp>();
	if (statusComp)
	{
		Status currentStatus = statusComp->GetPlayerInfo().status;
		Status itemStatus = unequippedItem->GetItemStatus();
		statusComp->GetPlayerInfo().status.RemoveStatus(currentStatus, itemStatus);
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


