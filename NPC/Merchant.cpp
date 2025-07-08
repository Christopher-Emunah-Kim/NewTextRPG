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

EMerchantResult Merchant::SellItem(int32 itemId, Player& player)
{
	if (m_salesStatusTable.find(itemId) == m_salesStatusTable.end())
	{
		throw invalid_argument("Item not found in sales table. itemId : " + to_string(itemId));
	}

	const int32 buyingPrice = ItemDataTable::GetInstance()->GetItem(itemId)->GetBuyingPrice();
	if (player.CanAfford(buyingPrice) == false)
	{
		return EMerchantResult::NotEnoughGold;
	}

	const BaseItem* templateItem = ItemDataTable::GetInstance()->GetItem(itemId);
	BaseItem* newItem = templateItem->CreateItem(); 

	if (ItemDataTable::GetInstance()->IsEquippable(itemId))
	{
		EItemType itemType = newItem->GetItemType();
		bool alreadyEquipped = false;

		if (itemType == EItemType::Weapon && player.GetEquipment().GetEquippedItem(EItemType::Weapon) != nullptr)
		{
			alreadyEquipped = true;
		}
		else if (itemType == EItemType::Armor && player.GetEquipment().GetEquippedItem(EItemType::Armor) != nullptr)
		{
			alreadyEquipped = true;
		}

		if (alreadyEquipped)
		{
			newItem->AddItemCount(1);
			if (player.GetInventory().AddItem(newItem))
			{
				player.UseGold(buyingPrice);
				return EMerchantResult::AlreadyEquipped;
			}
			else
			{
				delete newItem;
			}
		}
		else
		{
			player.GetEquipment().EquipItem(newItem);
		}
	}
	else
	{
		newItem->AddItemCount(1);
		if (!player.GetInventory().AddItem(newItem))
		{
			delete newItem;
			return EMerchantResult::AlreadyEquipped;
		}
	}

	//m_salesStatusTable.erase(itemId);
	player.UseGold(buyingPrice);
	
	return EMerchantResult::Success;
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

