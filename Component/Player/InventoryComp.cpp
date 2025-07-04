#include "InventoryComp.h"
#include "../../Data/ItemDataTable.h"
#include "../../Core/GameInstance.h"
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

//bool InventoryComp::AddItem(int32 itemId, int16 count)
//{
//	if (m_inventoryItems.size() >= m_maxInventorySize)
//	{
//		return false; 
//	}
//
//	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
//	{
//		BaseItem* item = m_inventoryItems[i];
//		if (item && item->GetItemID() == itemId)
//		{
//			return item->AddItemCount(count);
//		}
//	}
//
//	const BaseItem* templateItem = ItemDataTable::GetInstance()->GetItem(itemId);
//	if (templateItem != nullptr)
//	{
//		BaseItem* newItem = templateItem->CreateItem();
//		if (newItem->AddItemCount(count))
//		{
//			m_inventoryItems.push_back(newItem);
//			GameInstance::GetInstance()->UpdateInvetoryItems(newItem->GetName());
//			return true;
//		}
//		else
//		{
//			delete newItem;
//			return false;
//		}
//	}
//
//	return false;
//}

bool InventoryComp::AddItem(BaseItem* item)
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
	GameInstance::GetInstance()->UpdateInvetoryItems(item->GetName());

	return true;
}

bool InventoryComp::RemoveItem(int32 itemId, int16 count)
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

bool InventoryComp::HasItem(int32 itemId, int16 count) const
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


BaseItem* InventoryComp::GetItem(int32 itemId) const
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

vector<BaseItem*> InventoryComp::GetItemsByType(EItemType type) const
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
