#include "InventoryItem.h"

InventoryItem::InventoryItem(int64 serialNumber, int32 itemId)
: m_serialNumber(serialNumber), m_itemId(itemId)
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

InventoryItem InventoryItem::Create(int32 itemId)
{
	const int64 serialNumber = CreateSerialNumber();

	return InventoryItem(serialNumber, itemId);
}
