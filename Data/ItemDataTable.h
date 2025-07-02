#pragma once
#include "../Common.h"
#include "../Util/Type/EnumType.h"
#include "../Util/Singleton.h"

class BaseItem;

using ItemUMap = unordered_map<wstring, BaseItem*>;

constexpr __int16 CSV_COLUMN_NUM = 9;

class ItemDataTable final : public Singleton<ItemDataTable>
{
public:
	ItemDataTable() = default;
	virtual ~ItemDataTable();

private:
	ItemUMap m_itemDataTable;

public:
	void Init();
	void Release();

	bool HasItem(const wstring& itemName) const;
	wstring StringToWString(const string& str) const;
	EItemType StringToItemType(const string& itemType) const;
	BaseItem* CreateItem(const wstring& itemName) const;
	void  ProcessCSVParsing();


	const BaseItem* GetItem(const wstring& itemName) const;
	const ItemUMap& GetItemDataTable() const noexcept;
	const vector<wstring> GetItemNames() const noexcept;
	
};
