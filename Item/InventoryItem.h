#pragma once
#include "../Common.h"

class InventoryItem final
{
private:
	InventoryItem(int64 serialNumber, int32 itemId, int16 count);

public:
	virtual ~InventoryItem() = default;

	InventoryItem(const InventoryItem&) = delete;
	InventoryItem& operator=(const InventoryItem&) = delete;

	InventoryItem(InventoryItem&&) = default;
	InventoryItem& operator=(InventoryItem&&) = default;

	bool operator==(const InventoryItem& other) const noexcept
	{
		return m_serialNumber == other.m_serialNumber;
	}
	bool operator!=(const InventoryItem& other) const noexcept
	{
		return !(*this == other);
	}

private:
	static int64 CreateSerialNumber();

public:
	

	static InventoryItem Create(int32 itemId, int16 count = 1);
	void AddCount(int16 amount);
	bool RemoveCount(int16 amount);
	bool IsEmpty();

	int64 GetSerialNumber() const { return m_serialNumber; }
	int32 GetItemId() const { return m_itemId; }
	int16 GetCount() const { return m_count; }

private:
	int64 m_serialNumber;
	int32 m_itemId;
	int16 m_count;

};

