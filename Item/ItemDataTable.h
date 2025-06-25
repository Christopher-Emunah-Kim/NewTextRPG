#pragma once
#include "../Common.h"
#include "../Util/Singleton.h"

class BaseItem;

using ItemUMap = unordered_map<wstring, BaseItem*>;

class ItemDataTable final : public Singleton<ItemDataTable>
{
public:
	ItemDataTable() = default;
	virtual ~ItemDataTable() = default;

private:
	ItemUMap m_itemDataTable;

public:
	void Init();
	bool HasItem(const wstring& itemName) const;
	BaseItem* CreateItem(const wstring& itemName) const;

	const BaseItem* GetItem(const wstring& itemName) const;
	const ItemUMap& GetItemDataTable() const noexcept;
}

