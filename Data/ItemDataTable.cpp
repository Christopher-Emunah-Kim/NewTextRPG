#include "ItemDataTable.h"
#include "../Core/GameInstance.h"
#include "../Item/BaseItem.h"
#include "../Util/Type/EnumType.h"
#include "../Util/OutputSystem.h"

#include "../include/parser.hpp"


using namespace aria::csv;

//using json = nlohmann::json;

ItemDataTable::~ItemDataTable()
{
	Release();
}

void ItemDataTable::Init()
{
	//CSV PARSING
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
		if (row.size() < CSV_COLUMN_NUM)
		{
			GameInstance::GetInstance()->WriteLine(L"잘못된 열 수를 가진 CSV 행 발견, 건너뜁니다.");
			continue;
		}

		itemId = (int32)stoi(row[0]);
		nameStr = row[1];
		typeStr = row[2];
		descStr = row[3];
		buyingPrice = (int16)stoi(row[4]);
		sellingPrice = (int16)stoi(row[5]);
		itemAttack = (int16)stoi(row[6]);
		itemDefense = (int16)stoi(row[7]);
		itemAgility = (int16)stoi(row[8]);


		wstring name = StringToWString(nameStr); 
		wstring desc = StringToWString(descStr);

		BaseItem* item = new BaseItem(
			itemId,
			name,
			StringToItemType(typeStr),
			desc,
			buyingPrice, sellingPrice,
			itemAttack, itemDefense, itemAgility
		);


		m_itemDataTable[name] = item;
	}
}

void ItemDataTable::Release()
{
	for (unordered_map<wstring, BaseItem*>::iterator it = m_itemDataTable.begin(); it != m_itemDataTable.end(); ++it)
	{
		if (it->second)
		{
			delete it->second;
			it->second = nullptr;
		}
	}
	m_itemDataTable.clear();
}

bool ItemDataTable::HasItem(const wstring& itemName) const
{
	return m_itemDataTable.find(itemName) != m_itemDataTable.end();
}

wstring ItemDataTable::StringToWString(const string& str) const
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

EItemType ItemDataTable::StringToItemType(const string& itemType) const
{
	if (itemType == "Weapon")
	{
		return EItemType::Weapon;
	}
	else if (itemType == "Armor")
	{
		return EItemType::Armor;
	}
	else if (itemType == "Consumable")
	{
		return EItemType::Consumable;
	}
	else if (itemType == "Material")
	{
		return EItemType::Material;
	}

	GameInstance::GetInstance()->WriteLine(L"알 수 없는 아이템 타입: " + wstring(itemType.begin(), itemType.end()));
	return EItemType::Material;
}


BaseItem* ItemDataTable::CreateItem(const wstring& itemName) const
{
	unordered_map<wstring, BaseItem*>::const_iterator it = m_itemDataTable.find(itemName);
	if (it != m_itemDataTable.end())
	{
		return it->second->CreateItem();
	}
	GameInstance::GetInstance()->WriteLine(L"존재하지 않는 아이템입니다: " + itemName);
	return nullptr;
}

const BaseItem* ItemDataTable::GetItem(const wstring& itemName) const
{
	unordered_map<wstring, BaseItem*>::const_iterator it = m_itemDataTable.find(itemName);
	if (it != m_itemDataTable.end())
	{
		return it->second;
	}
	GameInstance::GetInstance()->WriteLine(L"존재하지 않는 아이템입니다: " + itemName);
	return nullptr;
}

const ItemUMap& ItemDataTable::GetItemDataTable() const noexcept
{
	return m_itemDataTable;
}

const vector<wstring> ItemDataTable::GetItemNames() const noexcept
{
	vector<wstring> itemNames;

	for (unordered_map<wstring, BaseItem*>::const_iterator it = m_itemDataTable.begin(); it != m_itemDataTable.end(); ++it)
	{
		itemNames.push_back(it->first);
	}

	return itemNames;
}