#include "Merchant.h"
#include "Data/ItemDataTable.h"
#include "Item/BaseItem.h"
#include "Item/InventoryItem.h"
#include "Character/Player.h"

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

expected<int32, wstring> Merchant::SellItem(int32 itemId, Player& player)
{
	if (m_salesStatusTable.find(itemId) == m_salesStatusTable.end())
	{
		return unexpected(wstring(L"해당 아이템은 상인의 보유아이템 목록에 존재하지 않습니다. itemId : ") + to_wstring(itemId));
	}

	const BaseItem* item = ItemDataTable::GetInstance()->GetItem(itemId);
	if (item == nullptr)
	{
		return unexpected(L"아이템 정보를 불러올 수 없습니다.");
	}

	if (player.CanAfford(item->GetBuyingPrice()) == false)
	{
		return unexpected(wstring(L"금액이 부족합니다."));
	}

	player.UseGold(item->GetBuyingPrice());

	return itemId;
}

expected<bool, wstring> Merchant::BuyItem(int32 itemId, Player& player)
{
	const BaseItem* targetItem = ItemDataTable::GetInstance()->GetItem(itemId);
	if (targetItem)
	{
		player.GainGold(targetItem->GetSellingPrice());

		return true;
	}
	else
	{
		return unexpected(wstring(L"아이템이 테이블에 없습니다. itemId : " + to_wstring(itemId)));
	}
}

