#include "InventoryComp.h"
#include "../../Item/ItemDataTable.h"
#include "../../Object/BaseGameObject.h"

InventoryComp::InventoryComp(BaseGameObject* owner)
	: BaseComponent(owner, 10), m_maxInventorySize(20)
{
}

void InventoryComp::Release()
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

bool InventoryComp::AddItem(const wstring& itemName, int16 count)
{
	if (m_inventoryItems.size() >= m_maxInventorySize)
	{
		return false; 
	}

	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* item = m_inventoryItems[i];
		if (item && item->GetName() == itemName)
		{
			return item->AddItemCount(count);
		}
	}

	BaseItem* newItem = ItemDataTable::GetInstance()->CreateItem(itemName);
	if (newItem != nullptr)
	{
		if (newItem->AddItemCount(count))
		{
			m_inventoryItems.push_back(newItem);
			return true;
		}
		else
		{
			delete newItem;
			return false;
		}
	}

	return false;
}

bool InventoryComp::AddItem(BaseItem* item)
{
	if (item == nullptr || m_inventoryItems.size() >= m_maxInventorySize)
	{
		return false;
	}

	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* existingItem = m_inventoryItems[i];
		if (existingItem && existingItem->GetName() == item->GetName())
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

	return true;
}

bool InventoryComp::RemoveItem(const wstring& itemName, int16 count)
{
	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* item = m_inventoryItems[i];
		if (item && item->GetName() == itemName)
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

BaseItem* InventoryComp::GetItem(const wstring& itemName) const
{
	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		BaseItem* item = m_inventoryItems[i];
		if (item && item->GetName() == itemName)
		{
			return item;
		}
	}
	return nullptr;
}

Status InventoryComp::GetTotalStatus() const
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
