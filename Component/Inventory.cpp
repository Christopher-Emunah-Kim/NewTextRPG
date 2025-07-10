#include "Inventory.h"
#include "../Data/ItemDataTable.h"
//#include "../Core/GameInstance.h"
//#include "../Object/BaseGameObject.h"

Inventory::Inventory()
	:  m_maxInventorySize(DEFAULT_INVENTORY_MAX_COUNT)
{}

Inventory::~Inventory()
{
	Release();
}

void Inventory::Release()
{
	m_inventoryItems.clear();
}

bool Inventory::AddItem(int32 itemId, int16 count)
{
	if ((int)m_inventoryItems.size() >= m_maxInventorySize)
	{
		return false;
	}

	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		InventoryItem& existingItem = m_inventoryItems[i];
		if (existingItem.GetItemId() == itemId)
		{
			existingItem.AddCount(count);
			
			return true;
		}
	}

	m_inventoryItems.push_back(InventoryItem::Create(itemId, count));

	return true;
}

bool Inventory::RemoveItem(int32 itemId, int16 count)
{

	for (vector<InventoryItem>::iterator it = m_inventoryItems.begin(); it != m_inventoryItems.end();  )
	{
		if (it->GetItemId() == itemId)
		{
			if (it->RemoveCount(count))
			{
				if (it->IsEmpty())
				{
					m_inventoryItems.erase(it); 
				}
				else
				{
					++it;
				}
				return true;
			}
			return false;
		}
		else
		{
			++it;
		}
	}
	return false;
}



InventoryItem Inventory::GetItem(int32 itemId) const
{
	for (size_t i = 0; i < m_inventoryItems.size(); ++i)
	{
		int32 targetId = m_inventoryItems[i].GetItemId();
		if (targetId == itemId)
		{
			return InventoryItem::Create(itemId);
		}
	}
}

