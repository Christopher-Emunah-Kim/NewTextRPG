#include "Inventory.h"
#include "../Data/ItemDataTable.h"
#include "../Core/GameInstance.h"
#include "../Object/BaseGameObject.h"

Inventory::Inventory()
	:  m_maxInventorySize(DEFAULT_INVENTORY_MAX_COUNT)
{}

Inventory::~Inventory()
{
	Release();
}

void Inventory::Release()
{
	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* item = m_inventoryItems[i];
		if (item)
		{
			delete item;
			item = nullptr;
		}
	}
	m_inventoryItems.clear();
}

bool Inventory::AddItem(BaseItem* item)
{
	
	if (item == nullptr || m_inventoryItems.size() >= m_maxInventorySize)
	{
		return false;
	}

	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* existingItem = m_inventoryItems[i];
		if (existingItem && existingItem->GetItemID() == item->GetItemID())
		{
			bool result = existingItem->AddItemCount(item->GetCount());
			/*if (result)
			{
				delete item;
			}*/
			return result;
		}
	}
	m_inventoryItems.push_back(item);

	return true;
}

bool Inventory::RemoveItem(int32 itemId, int16 count)
{
	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* item = m_inventoryItems[i];
		if (item && item->GetItemID() == itemId)
		{
			if (item->RemoveItemCount(count))
			{
				if (item->IsEmpty())
				{
					delete item;
					m_inventoryItems.erase(m_inventoryItems.begin() + i);
				}

				return true;
			}
			return false;
		}
	}
	return false;
}



BaseItem* Inventory::GetItem(int32 itemId) const
{
	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* item = m_inventoryItems[i];
		if (item && item->GetItemID() == itemId)
		{
			return item;
		}
	}
	return nullptr;
}


Status Inventory::GetTotalStatus() const
{
	int16 atk = 0;
	int16 def = 0;
	int16 agi = 0;

	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* item = m_inventoryItems[i];
		if (item)
		{
			Status itemStatus = item->GetItemStatus();
			atk += itemStatus.GetAttack();
			def += itemStatus.GetDefense();
			agi += itemStatus.GetAgility();
		}
	}

	return Status::NewStatus(atk, def, agi);
}
