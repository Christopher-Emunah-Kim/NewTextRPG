#include "Inventory.h"
#include "../Data/ItemDataTable.h"
#include "../Core/GameInstance.h"
#include "../Object/BaseGameObject.h"

Inventory::Inventory(BaseGameObject* owner)
	: m_owner(owner), m_maxInventorySize(20)
{
}

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
			if (result)
			{
				delete item;
			}
			return result;
		}
	}
	m_inventoryItems.push_back(item);
	GameInstance::GetInstance()->UpdateInvetoryItems(m_inventoryItems);

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

bool Inventory::HasItem(int32 itemId, int16 count) const
{
	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* item = m_inventoryItems[i];
		if (item && item->GetItemID() == itemId && item->GetCount() >= count)
		{
			return true;
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

vector<BaseItem*> Inventory::GetItemsByType(EItemType type) const
{
	vector<BaseItem*> resultItems;

	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* item = m_inventoryItems[i];
		if (item && item->GetItemType() == type)
		{
			resultItems.push_back(item);
		}
	}

	return resultItems;

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
