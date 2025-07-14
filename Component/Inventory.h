#pragma once
#include "Common.h"
#include "../Item/InventoryItem.h"

constexpr int16 DEFAULT_INVENTORY_MAX_COUNT = 99;

class Inventory final
{
public:
	explicit Inventory();
	virtual ~Inventory();

public:
	void Release();

	void Use(int32 itemId, int32 count = 1);
	bool AddItem(int32 itemId, int16 count = 1);
	bool RemoveItem(int32 itemId, int16 count = 1);
	const InventoryItem* GetItem(int32 itemId) const;

	inline const vector<InventoryItem>& GetInventoryItems() const { return m_inventoryItems; }

private:
	vector<InventoryItem> m_inventoryItems;
	int16 m_maxInventorySize = DEFAULT_INVENTORY_MAX_COUNT;
};

