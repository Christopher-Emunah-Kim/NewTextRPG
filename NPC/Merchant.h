#pragma once
#include "Common.h"

enum class EMerchantResult
{
	Success,
	NotEnoughGold
};

class Player;

class Merchant final
{
public:
	Merchant() = default;

	void AddSaleItem(int32 itemId);
	vector<int32> GetSalesItems() const;
	EMerchantResult SellItem(int32 itemId, Player& player);

private:
	map<int32, bool> m_salesStatusTable;
};