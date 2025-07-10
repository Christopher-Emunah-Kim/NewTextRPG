#include "InventoryItem.h"

InventoryItem::InventoryItem(int64 serialNumber, int32 itemId, int16 count)
: m_serialNumber(serialNumber), m_itemId(itemId), m_count(count)
{
}

int64 InventoryItem::CreateSerialNumber()
{
	const time_point now = system_clock::now();
	const int64 timestamp = duration_cast<milliseconds>(now.time_since_epoch()).count();

	srand(static_cast<unsigned int>(time(NULL)));
	const int32 randomNumber = rand() % 1000000; 

	stringstream ss;
	ss << timestamp << setfill('0') << setw(6) << randomNumber;
	return stoll(ss.str());
}

InventoryItem InventoryItem::Create(int32 itemId, int16 count)
{
	const int64 serialNumber = CreateSerialNumber();

	return InventoryItem(serialNumber, itemId, count);
}

void InventoryItem::AddCount(int16 amount)
{
	m_count += amount;
}

bool InventoryItem::RemoveCount(int16 amount)
{
	if (m_count < amount)
	{
		return false;
	}
	m_count -= amount;
	return true;
}

bool InventoryItem::IsEmpty()
{
	return m_count <= 0;
}
