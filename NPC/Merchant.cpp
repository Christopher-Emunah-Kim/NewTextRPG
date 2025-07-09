#include "Merchant.h"
#include "Data/ItemDataTable.h"
#include "Item/BaseItem.h"
#include "Object/Character/Player.h"

void Merchant::AddSaleItem(int32 itemId)
{
	m_salesStatusTable[itemId] = true;
}

vector<int32> Merchant::GetSalesItems() const
{
	vector<int32> saleItems;
	for (map<int32, bool>::const_iterator it = m_salesStatusTable.begin(); it != m_salesStatusTable.end(); ++it)
	{
		if (it->second)
		{
			saleItems.push_back(it->first);
		}
	}

	return saleItems;
}

expected<BaseItem*, wstring> Merchant::SellItem(int32 itemId, Player& player)
{
	if (m_salesStatusTable.find(itemId) == m_salesStatusTable.end())
	{
		return unexpected(wstring(L"해당 아이템은 상인의 보유아이템 목록에 존재하지 않습니다. itemId : ") + to_wstring(itemId));
	}

	const int32 buyingPrice = ItemDataTable::GetInstance()->GetItem(itemId)->GetBuyingPrice();
	if (player.CanAfford(buyingPrice) == false)
	{
		return unexpected(wstring(L"금액이 부족합니다."));
	}

	player.UseGold(buyingPrice);
	
	const BaseItem* templateItem = ItemDataTable::GetInstance()->GetItem(itemId);
	BaseItem* item = templateItem->CreateItem();

	return item;
}

void Merchant::BuyItem(int32 itemId, Player& player)
{
	const BaseItem* targetItem = ItemDataTable::GetInstance()->GetItem(itemId);
	if (targetItem)
	{
		const int32 sellingPrice = targetItem->GetSellingPrice();

		player.GainGold(sellingPrice);
	}
	else
	{
		throw invalid_argument("아이템이 테이블에 없습니다. itemId : " + to_string(itemId));
	}
}

