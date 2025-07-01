#include "ItemDataTable.h"
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

	//JSON PARSING
	/*ifstream file("Data/ItemJsonData.json");

	if (!file.is_open())
	{
		OutputSystem::PrintErrorMsg(L"아이템 JSON 파일을 열 수 없습니다.");
		return;
	}

	json itemJson;
	file >> itemJson;

	for (json::iterator it = itemJson.begin(); it != itemJson.end(); ++it)
	{
		const json& itemJson = *it;
		string nameStr = itemJson["name"];
		string typeStr = itemJson["type"];
		string descStr = itemJson["description"];
		json values = itemJson["values"];

		wstring name(nameStr.begin(), nameStr.end());
		wstring desc(descStr.begin(), descStr.end());

		BaseItem* item = new BaseItem(
			name,
			StringToItemType(typeStr),
			desc,
			values[0], values[1], values[2], values[3], values[4]
		);

		m_itemDataTable[name] = item;
	}*/

}

void ItemDataTable::ProcessCSVParsing()
{
	ifstream file("Data/ItemCSVData.csv");
	if (!file.is_open())
	{
		OutputSystem::PrintErrorMsg(L"CSV 파일을 열 수 없습니다: Data/ItemCSVData.csv");
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
			OutputSystem::PrintErrorMsg(L"잘못된 열 수를 가진 CSV 행 발견, 건너뜁니다.");
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


		wstring name(nameStr.begin(), nameStr.end());
		wstring desc(descStr.begin(), descStr.end());

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

	OutputSystem::PrintErrorMsg(L"알 수 없는 아이템 타입: " + wstring(itemType.begin(), itemType.end()));
	return EItemType::Material;
}


BaseItem* ItemDataTable::CreateItem(const wstring& itemName) const
{
	unordered_map<wstring, BaseItem*>::const_iterator it = m_itemDataTable.find(itemName);
	if (it != m_itemDataTable.end())
	{
		return it->second->CreateItem();
	}
	OutputSystem::PrintErrorMsg(L"존재하지 않는 아이템입니다: " + itemName);
	return nullptr;
}

const BaseItem* ItemDataTable::GetItem(const wstring& itemName) const
{
	unordered_map<wstring, BaseItem*>::const_iterator it = m_itemDataTable.find(itemName);
	if (it != m_itemDataTable.end())
	{
		return it->second;
	}
	OutputSystem::PrintErrorMsg(L"존재하지 않는 아이템입니다: " + itemName);
	return nullptr;
}

const ItemUMap& ItemDataTable::GetItemDataTable() const noexcept
{
	return m_itemDataTable;
}
