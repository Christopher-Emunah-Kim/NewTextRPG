#pragma once
#include "BaseComponent.h"
#include "../Item/BaseItem.h"


constexpr int16 DEFAULT_INVENTORY_MAX_COUNT = 99;

class Inventory final
{
public:
	explicit Inventory();
	~Inventory();

public:
	void Release();

	bool AddItem(BaseItem* item);
	bool RemoveItem(int32 itemId, int16 count = 1);

	BaseItem* GetItem(int32 itemId) const;
	Status GetTotalStatus() const;

	inline const vector<BaseItem*> GetInventoryItems() const { return m_inventoryItems; }

private:
	vector<BaseItem*> m_inventoryItems; 
	int16 m_maxInventorySize = DEFAULT_INVENTORY_MAX_COUNT;
};

