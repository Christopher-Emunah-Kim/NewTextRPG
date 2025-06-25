#include "ItemDataTable.h"
#include "../Util/Type/EnumType.h"
#include "BaseItem.h"
#include "../Util/OutputSystem.h"

void ItemDataTable::Init()
{
	// Weapon
	m_itemDataTable[L"철검"] = new BaseItem(L"철검", EItemType::Weapon,
		L"기본적인 철제 검입니다.", 100, 50, 5, 0, 0);

	m_itemDataTable[L"예리한 대검"] = new BaseItem(L"예리한 대검", EItemType::Weapon,
		L"강력한 공격력을 지닌 대검입니다.", 250, 125, 12, 0, 2);

	m_itemDataTable[L"신속한 단검"] = new BaseItem(L"신속한 단검", EItemType::Weapon,
		L"빠르게 공격할 수 있는 단검입니다.", 150, 75, 3, 0, 8);

	// Armor
	m_itemDataTable[L"가죽 갑옷"] = new BaseItem(L"가죽 갑옷", EItemType::Armor,
		L"기본적인 가죽 갑옷입니다.", 80, 40, 0, 4, 1);

	m_itemDataTable[L"강철 갑옷"] = new BaseItem(L"강철 갑옷", EItemType::Armor,
		L"튼튼한 강철 갑옷입니다.", 200, 100, 0, 10, -3);

	m_itemDataTable[L"경량 갑옷"] = new BaseItem(L"경량 갑옷", EItemType::Armor,
		L"가볍고 움직임이 자유로운 갑옷입니다.", 180, 90, 0, 6, 5);

	// Consumable
	m_itemDataTable[L"체력 포션"] = new BaseItem(L"체력 포션", EItemType::Consumable,
		L"체력을 회복시켜주는 물약입니다.", 30, 15, 0, 0, 0);

	// Material
	m_itemDataTable[L"고블린 뼈"] = new BaseItem(L"고블린 뼈", EItemType::Material,
		L"고블린에게서 얻을 수 있는 뼈입니다.", 5, 2, 0, 0, 0);

	//TODO: CSV 파일에서 아이템 데이터 로드 구현
}

bool ItemDataTable::HasItem(const wstring& itemName) const
{
	return m_itemDataTable.find(itemName) != m_itemDataTable.end();
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
