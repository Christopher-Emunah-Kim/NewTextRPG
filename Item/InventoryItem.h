#pragma once
#include "../Common.h"

class InventoryItem
{
private:
	InventoryItem(int64 serialNumber, int32 itemId, int16 count);

public:
	virtual ~InventoryItem() = default;

	InventoryItem(const InventoryItem&) = delete;
	InventoryItem& operator=(const InventoryItem&) = delete;

	InventoryItem(InventoryItem&&) = default;
	InventoryItem& operator=(InventoryItem&&) = default;

private:
	static int64 CreateSerialNumber();

public:
	static InventoryItem Create(int32 itemId, int16 count = 1);
	void AddCount(int16 amount = 1);
	bool RemoveCount(int16 amount = 1);
	bool IsEmpty();

	int64 GetSerialNumber() const { return m_serialNumber; }
	int32 GetItemId() const { return m_itemId; }
	int16 GetCount() const { return m_count; }

private:
	const int64 m_serialNumber;
	const int32 m_itemId;
	int16 m_count;

};

