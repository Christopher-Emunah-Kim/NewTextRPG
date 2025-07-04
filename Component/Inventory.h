#pragma once
#include "BaseComponent.h"
#include "../Item/BaseItem.h"

class Inventory final
{
public:
	Inventory(BaseGameObject* owner);
	virtual ~Inventory();

public:
	virtual void Release();

	bool AddItem(BaseItem* item);
	bool RemoveItem(int32 itemId, int16 count = 1);
	bool HasItem(int32 itemId, int16 count = 1) const;

	BaseItem* GetItem(int32 itemId) const;
	vector<BaseItem*> GetItemsByType(EItemType type) const;
	Status GetTotalStatus() const;

	inline const vector<BaseItem*> GetInventoryItems() const { return m_inventoryItems; }
	inline const int16& GetMaxInventorySize() const { return m_maxInventorySize; }
	inline void SetMaxInventorySize(int16 size) { m_maxInventorySize = size; }
	inline bool IsInventoryFull() const { return m_inventoryItems.size() >= m_maxInventorySize; }

private:
	BaseGameObject* m_owner = nullptr;
	vector<BaseItem*> m_inventoryItems; 
	int16 m_maxInventorySize = DEFAULT_ITEM_MAX_COUNT;
};

