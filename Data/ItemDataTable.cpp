#include "ItemDataTable.h"
#include "include/parser.hpp"
#include "../Core/GameInstance.h"
#include "../Item/BaseItem.h"
#include "../Util/Type/EnumType.h"
#include "../Util/OutputSystem.h"



using namespace aria::csv;


ItemDataTable::~ItemDataTable()
{
	Release();
}

void ItemDataTable::Init()
{
	ProcessCSVParsing();
}

void ItemDataTable::ProcessCSVParsing()
{
	ifstream file("Data/ItemCSVData.csv");
	if (!file.is_open())
	{
		GameInstance::GetInstance()->WriteLine(L"CSV 파일을 열 수 없습니다: Data/ItemCSVData.csv");
		return;
	}

	CsvParser parser(file);
	bool headerSkipped = false;

	int32 itemId;
	string nameStr, typeStr, descStr;
	int16 buyingPrice, sellingPrice, itemAttack, itemDefense, itemAgility;

	for (CsvParser::iterator it = parser.begin(); it != parser.end(); ++it)
	{
		const vector<string>& row = *it;
		if (headerSkipped == false)
		{
			headerSkipped = true;
			continue;
		}

		itemId = (int32)stoi(row[0]);
		nameStr = row[1];
		descStr = row[2];
		buyingPrice = (int16)stoi(row[3]);
		sellingPrice = (int16)stoi(row[4]);
		itemAttack = (int16)stoi(row[5]);
		itemDefense = (int16)stoi(row[6]);
		itemAgility = (int16)stoi(row[7]);


		wstring name = ToWideStr(nameStr); 
		wstring desc = ToWideStr(descStr);

		BaseItem* item = new BaseItem(
			itemId,
			name,
			GetItemType(itemId),
			desc,
			buyingPrice, sellingPrice,
			itemAttack, itemDefense, itemAgility
		);

		m_itemDataTable[itemId] = item;
	}
}

const BaseItem* ItemDataTable::GetItem(int32 itemId) const
{
	if (m_itemDataTable.find(itemId) == m_itemDataTable.end())
	{
		throw invalid_argument("존재하지 않는 아이템 ID: " + to_string(itemId));
	}

	return m_itemDataTable.at(itemId);
}

vector<int32> ItemDataTable::GetItemIds() const
{
	vector<int32> itemIds;
	for (unordered_map<int32, BaseItem*>::const_iterator it = m_itemDataTable.begin(); it != m_itemDataTable.end(); ++it)
	{
		itemIds.push_back(it->first);
	}
	return itemIds;
}

wstring ItemDataTable::ToWideStr(const string& str)
{
	if (str.empty())
	{
		return wstring();
	}

	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);

	wstring resultWstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &resultWstr[0], size_needed);

	return resultWstr;
}

void ItemDataTable::Release()
{
	for (unordered_map<int32, BaseItem*>::iterator it = m_itemDataTable.begin(); it != m_itemDataTable.end(); ++it)
	{
		if (it->second)
		{
			delete it->second;
			it->second = nullptr;
		}
	}
	m_itemDataTable.clear();
}

EItemType ItemDataTable::GetItemType(int32 itemId) const
{
	const int32 typeDigit = itemId / 10000;
	switch (typeDigit)
	{
	case 1:
		return EItemType::Weapon;
	case 2:
		return EItemType::Armor;
	case 3:
		return EItemType::Consumable;
	case 4:
		return EItemType::Material;

	default:
		throw invalid_argument("알 수 없는 아이템 ID: " + to_string(itemId));
	}
}

bool ItemDataTable::IsEquippable(int32 itemId) const
{
	EItemType itemType = GetItemType(itemId);
	if (itemType == EItemType::Material || itemType == EItemType::Consumable)
	{
		return false;
	}
	else
	{
		return true;
	}
}
