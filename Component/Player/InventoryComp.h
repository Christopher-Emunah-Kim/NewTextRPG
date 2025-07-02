#pragma once
#include "../BaseComponent.h"
#include "../../Item/BaseItem.h"

class InventoryComp final : public BaseComponent
{
public:
	InventoryComp(BaseGameObject* owner);
	virtual ~InventoryComp() = default;

private:
	vector<BaseItem*> m_inventoryItems; 
	int16 m_maxInventorySize = DEFAULT_ITEM_MAX_COUNT;

public:
	virtual void Release() override;

	bool AddItem(const wstring& itemName, int16 count = 1);
	bool AddItem(BaseItem* item);
	bool RemoveItem(const wstring& itemName, int16 count = 1);
	bool HasItem(const wstring& itemName, int16 count = 1) const;

	BaseItem* GetItem(const wstring& itemName) const;
	vector<BaseItem*> GetItemsByType(EItemType type) const;
	Status GetTotalStatus() const;

	inline const vector<BaseItem*> GetInventoryItems() const { return m_inventoryItems; }
	inline const int16& GetMaxInventorySize() const { return m_maxInventorySize; }
	inline void SetMaxInventorySize(int16 size) { m_maxInventorySize = size; }
	inline bool IsInventoryFull() const { return m_inventoryItems.size() >= m_maxInventorySize; }
};

