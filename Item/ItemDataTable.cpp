#include "ItemDataTable.h"
#include "BaseItem.h"
#include "../Util/Type/EnumType.h"
#include "../Util/OutputSystem.h"

using json = nlohmann::json;

ItemDataTable::~ItemDataTable()
{
	Release();
}

void ItemDataTable::Init()
{
	ifstream file("Data/ItemJsonData.json");

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
	}



	//// Weapon
	//m_itemDataTable[L"철검"] = new BaseItem(L"철검", EItemType::Weapon,
	//	L"기본적인 철제 검입니다.", 100, 50, 5, 0, 0);

	//m_itemDataTable[L"예리한 대검"] = new BaseItem(L"예리한 대검", EItemType::Weapon,
	//	L"강력한 공격력을 지닌 대검입니다.", 250, 125, 12, 0, 2);

	//m_itemDataTable[L"신속한 단검"] = new BaseItem(L"신속한 단검", EItemType::Weapon,
	//	L"빠르게 공격할 수 있는 단검입니다.", 150, 75, 3, 0, 8);

	//// Armor
	//m_itemDataTable[L"가죽 갑옷"] = new BaseItem(L"가죽 갑옷", EItemType::Armor,
	//	L"기본적인 가죽 갑옷입니다.", 80, 40, 0, 4, 1);

	//m_itemDataTable[L"강철 갑옷"] = new BaseItem(L"강철 갑옷", EItemType::Armor,
	//	L"튼튼한 강철 갑옷입니다.", 200, 100, 0, 10, -3);

	//m_itemDataTable[L"경량 갑옷"] = new BaseItem(L"경량 갑옷", EItemType::Armor,
	//	L"가볍고 움직임이 자유로운 갑옷입니다.", 180, 90, 0, 6, 5);

	//// Consumable
	//m_itemDataTable[L"체력 포션"] = new BaseItem(L"체력 포션", EItemType::Consumable,
	//	L"체력을 회복시켜주는 물약입니다.", 30, 15, 0, 0, 0);

	//// Material
	//m_itemDataTable[L"고블린 뼈"] = new BaseItem(L"고블린 뼈", EItemType::Material,
	//	L"고블린에게서 얻을 수 있는 뼈입니다.", 5, 2, 0, 0, 0);

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
