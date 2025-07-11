#pragma once
#include "Common.h"

class Player;
class InventoryItem;

class Merchant final
{
public:
	Merchant() = default;

	void AddSaleItem(int32 itemId);
	vector<int32> GetSalesItems() const;
	expected<int32, wstring> SellItem(int32 itemId, Player& player);
	expected<bool, wstring> BuyItem(int32 itemId, Player& player);

private:
	map<int32, bool> m_salesStatusTable;
};