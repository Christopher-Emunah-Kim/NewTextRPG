#pragma once
#include "../Common.h"
#include "../Util/Type/EnumType.h"
#include "../Util/Singleton.h"

class BaseItem;

class ItemDataTable final : public Singleton<ItemDataTable>
{
public:
	ItemDataTable() = default;
	virtual ~ItemDataTable();

	void Init();
	void Release();
	bool IsEquippable(int32 itemId) const;

	const BaseItem* GetItem(int32 itemId) const;
	vector<int32> GetItemIds() const;

private:
	void  ProcessCSVParsing();
	static wstring ToWideStr(const string& str);
	EItemType GetItemType(int32 itemId) const;

private:
	unordered_map<int32, BaseItem*> m_itemDataTable;
};
