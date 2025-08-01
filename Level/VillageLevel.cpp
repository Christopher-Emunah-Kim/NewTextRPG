﻿#include "VillageLevel.h"
#include "../Core/GameInstance.h"
#include "../Core/LevelManager.h"
#include "../Util/InputSystem.h"
#include "../Item/BaseItem.h"
#include "Data/ItemDataTable.h"
#include "Component/Inventory.h"
#include "Component/Equipment.h"
#include "NPC/Healer.h"
#include "NPC/Merchant.h"

VillageLevel::~VillageLevel()
{
	delete m_healer;
	m_healer = nullptr;

	delete m_merchant;
	m_merchant = nullptr;
}

void VillageLevel::Init()
{
	constexpr int32 HEAL_COST = 100;
	m_healer = new Healer(HEAL_COST);

	m_merchant = new Merchant();
	//TODO : 랜덤 아이템 추가
	m_merchant->AddSaleItem(13001);
	m_merchant->AddSaleItem(12001);
	m_merchant->AddSaleItem(23001);
	m_merchant->AddSaleItem(22001);

	gi = GameInstance::GetInstance();

	ShowGreetingMenu();

	BaseLevel::Init();
}

void VillageLevel::ShowGreetingMenu()
{
	gi->ClearText();
	gi->WriteLine(L"============================================");
	gi->WriteLine();
	gi->WriteLine(L"당신은 마을에 도착했습니다.");
	gi->WriteLine(L"마을은 평화롭고 안전해 보입니다.");
	gi->WriteLine();
	gi->WriteLine(L"마을에서 무엇을 하시겠습니까?");
	gi->WriteLine();
	gi->WriteLine(L"[마을 메뉴 옵션]");
	gi->WriteLine();
	gi->WriteLine(L"1. 아이템 상점에 들어간다.");
	gi->WriteLine();
	gi->WriteLine(L"2. 치유사의 집에 들어간다.");
	gi->WriteLine();
	gi->WriteLine(L"3. 마을을 떠난다..");
	gi->WriteLine();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&VillageLevel::OnEnterItemShop, this)},
			{L"2", bind(&VillageLevel::OnEnterHealerShop, this)},
			{L"3", bind(&VillageLevel::OnExitVillage, this)},
		}
	);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			ShowGreetingMenu();
		}
	);
}

void VillageLevel::OnEnterItemShop()
{
	gi->WriteLine();
	gi->WriteLine(L"상점에 들어갑니다.");
	gi->WriteLine(L"상점 주인 월로드 가 당신을 반깁니다.");
	gi->WriteLine();
	gi->WriteLine(L"자네로군!! 호승심에 가득찬 새로운 모험가라지?");
	gi->WriteLine(L"재고는 충분하네! 원하는대로 골라봐!");
	gi->WriteLine();
	gi->WriteLine(L"상점에서 아이템을 구매하거나 판매할 수 있습니다.");
	gi->WriteLine(L"상점에서 무엇을 하시겠습니까?");
	gi->WriteLine();
	gi->WriteLine(L"1. 아이템 구매하기");
	gi->WriteLine();
	gi->WriteLine(L"2. 아이템 판매하기");
	gi->WriteLine();
	gi->WriteLine(L"3. 상점에서 나가기");
	gi->WriteLine();

	InputSystem::BindAction(
		{
			{L"1", bind(&VillageLevel::OnBuyItem, this)},
			{L"2", bind(&VillageLevel::OnSellItem, this)},
			{L"3", bind(&VillageLevel::ShowGreetingMenu, this)},
		}
		);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			ShowGreetingMenu();
		}
	);
}

void VillageLevel::OnBuyItem()
{
	gi->ClearText();

	gi->WriteLine();
	gi->WriteLine(L"상점에서 판매하는 아이템 목록을 보여줍니다.");
	gi->WriteLine();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"[판매 중인 아이템 목록]");
	gi->WriteLine();
	gi->WriteLine(L"0: 뒤로가기");
	gi->WriteLine();

	ItemDataTable* itemDataTable = ItemDataTable::GetInstance();
	vector<int32> salesItems = m_merchant->GetSalesItems();
	for (size_t index = 0; index < salesItems.size(); ++index)
	{
		const BaseItem* item = itemDataTable->GetItem(salesItems[index]);
		
		wstringstream ss;
		ss << index + 1 << L"." << item->GetName() <<
			L" - 가격: " << item->GetBuyingPrice() << L" 골드";

		if (itemDataTable->IsEquippable(item->GetItemID()))
		{
			ss << L" | " << item->GetItemStatus().ToString();
		}

		gi->WriteLine(ss.str());
		gi->WriteLine(L"-> " + item->GetDescription());
		gi->WriteLine(L"");
	}

	if (salesItems.empty()) 
	{
		gi->WriteLine(L"현재 판매 중인 상품이 없습니다.");
	}

	gi->WriteLine(L"============================================");
	gi->WriteLine(L"구매할 아이템 번호를 입력하세요");

	InputSystem::Clear();

	InputSystem::BindAction(L"0", bind(&VillageLevel::OnEnterItemShop, this));
	for (size_t index = 0; index < salesItems.size(); ++index)
	{
		InputSystem::BindAction(to_wstring(index + 1),
			bind(&VillageLevel::BuySelectedItem, this, salesItems[index]));
	}

 	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			OnBuyItem();
		}
	);
}

void VillageLevel::BuySelectedItem(int32 itemId)
{
	Player& player = gi->GetPlayer();

	expected<int32, wstring> expectedResult = m_merchant->SellItem(itemId, player);

	if(!expectedResult.has_value())
	{
		gi->WriteLine(expectedResult.error());
		return;
	}

	int32 newItemId = expectedResult.value();
	InventoryItem newItem = InventoryItem::Create(newItemId);

	EPlayerHandleItemResult itemHandleResult = player.HandlePurchasedItem(move(newItem));


	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(GetMsgForItemHandleResult(itemHandleResult, move(newItem)));
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(L"1. 계속 쇼핑하기");
	gi->WriteLine(L"2. 상점 메뉴로 돌아가기");


	const BaseItem* dbItem = ItemDataTable::GetInstance()->GetItem(newItemId);
	if (itemHandleResult == EPlayerHandleItemResult::Equipped)
	{
		gi->UpdateEquippedItem(dbItem->GetName(), dbItem->GetItemType());
	}
	else if (itemHandleResult == EPlayerHandleItemResult::AddToInventory)
	{
		gi->UpdateInvetoryItems(player.GetInventoryItems());
	}
	gi->UpdatePlayerGold(player.GetGoldForHUD());
	gi->UpdatePlayerStatus(player.GetTotalPlayerStatus());

	InputSystem::Clear();
	InputSystem::BindAction({
		{L"1", bind(&VillageLevel::OnBuyItem, this)},
		{L"2", bind(&VillageLevel::OnEnterItemShop, this)}
		});

}

wstring VillageLevel::GetMsgForItemHandleResult(EPlayerHandleItemResult result, InventoryItem item)
{
	const BaseItem* dbItem = ItemDataTable::GetInstance()->GetItem(item.GetItemId());

	switch (result)
	{
	case EPlayerHandleItemResult::Equipped:
	{
		
		return dbItem->GetName() + L"을(를) 장착했습니다!";
	}
	break;
	case EPlayerHandleItemResult::AddToInventory:
	{
		return dbItem->GetName() + L"을(를) 인벤토리에 추가했습니다.";
	}
	break;
	case EPlayerHandleItemResult::InventoryFull:
	{
		return L"인벤토리에 공간이 없어 " + dbItem->GetName()  + L"을(를) 버렸습니다.";
	}
	break;
	case EPlayerHandleItemResult::ItemNullPtr:
	{
		return L"아이템이 존재하지 않습니다. item : " + dbItem->GetName();
	}
	break;
	case EPlayerHandleItemResult::InvalidItemType:
	{
		return L"알 수 없는 아이템입니다.";
	}
	break;

	default:
	{
		return L"[오류] 알 수 없는 결과입니다.";
	}
	break;
	}
}

void VillageLevel::OnSellItem()
{
	Player& player = gi->GetPlayer();

	gi->WriteLine();
	gi->WriteLine(L"상인에게 판매 가능한 아이템 목록을 보여줍니다.");
	gi->WriteLine();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"[판매 가능한 아이템 목록]");
	gi->WriteLine();
	gi->WriteLine(L"0: 뒤로가기");
	gi->WriteLine();

	const vector<InventoryItem>& items = player.GetInventoryItems();
	ItemDataTable* itemDataTable = ItemDataTable::GetInstance();
	for (size_t index = 0; index < items.size(); ++index)
	{
		const BaseItem* item = itemDataTable->GetItem(items[index].GetItemId());

		wstringstream ss;
		ss << index + 1 << L"." << item->GetName() <<
			L" - 가격: " << item->GetSellingPrice() << L" 골드";
		\
		gi->WriteLine(ss.str());
	}
	if (items.empty())
	{
		gi->WriteLine(L"현재 판매 가능한 아이템이 없습니다.");
	}

	gi->WriteLine(L"============================================");
	gi->WriteLine(L"판매할 아이템 번호를 입력하세요");

	InputSystem::Clear();

	InputSystem::BindAction(L"0", bind(&VillageLevel::OnEnterItemShop, this));
	for (size_t index = 0; index < items.size(); ++index)
	{
		InputSystem::BindAction(to_wstring(index + 1),
			bind(&VillageLevel::SellSelectedItem, this, items[index].GetItemId()));
	}

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			OnSellItem();
		}
	);
}

void VillageLevel::SellSelectedItem(int32 itemId)
{
	Player& player = gi->GetPlayer();
	const BaseItem* item = ItemDataTable::GetInstance()->GetItem(itemId);

	expected<bool, wstring> expectedResult = m_merchant->BuyItem(itemId, player);

	if (!expectedResult.has_value())
	{
		gi->WriteLine(expectedResult.error());
		return;
	}

	bool bIsSucess = expectedResult.value();

	if (bIsSucess)
	{
		gi->ClearText();

		gi->WriteLine(L"상인은 흡족해하며 당신에게 받은 물품을 살펴봅니다.");
		player.RemoveItemFromInventory(itemId);
		gi->UpdatePlayerGold(player.GetGoldForHUD());
		gi->UpdateInvetoryItems(player.GetInventoryItems());

	}

	gi->WriteLine();
	gi->WriteLine(L"이제 어떻게 할까?");
	gi->WriteLine();
	gi->WriteLine();
	gi->WriteLine(L"1. 계속 판매하기");
	gi->WriteLine(L"2. 상점 메뉴로 돌아가기");

	InputSystem::BindAction({
		{L"1", bind(&VillageLevel::OnSellItem, this)},
		{L"2", bind(&VillageLevel::OnEnterItemShop, this)}
		});
}

void VillageLevel::OnEnterHealerShop()
{
	const wstring& playerName = gi->GetPlayer().GetBattleCharacterInfo().name;

	gi->WriteLine();
	gi->WriteLine(L"치유의 집에 들어갑니다.");
	gi->WriteLine(L"치유사 스칼드 가 당신을 반깁니다.");
	gi->WriteLine();
	gi->WriteLine(L"반가워요. 당신이 바로 그..." + playerName + L" 용사군요.");
	gi->WriteLine();
	gi->WriteLine(L"치유사가 당신의 상태를 살펴봅니다.");

	gi->WriteLine();
	gi->WriteLine(L"1. 퍼펙트 힐링 요청하기(소모골드 : " + to_wstring(m_healer->GetHealCost()) + L" )");
	gi->WriteLine();
	gi->WriteLine(L"2. 치유의 집에서 나가기");
	gi->WriteLine();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::Clear();
	InputSystem::BindAction(
		{
			{L"1", bind(&VillageLevel::OnRecoverPlayer, this)},
			{L"2", bind(&VillageLevel::ShowGreetingMenu, this)},
		}
		);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			ShowGreetingMenu();
		}
	);
}

void VillageLevel::OnRecoverPlayer()
{
	Player& player = gi->GetPlayer();

	expected<bool, wstring> expectedResult = m_healer->HealPlayer(player);


	if (!expectedResult.has_value())
	{
		gi->WriteLine(L"");
		gi->WriteLine(expectedResult.error());
		gi->WriteLine(L"");
		gi->WriteLine(L"치유의 집을 떠나 마을로 돌아갑니다..");
		gi->WriteLine(L"아무 버튼이나 입력하세요.");
		gi->WriteLine(L"");
		return;
	}

	bool bIsSucess = expectedResult.value();
	if (bIsSucess)
	{
		gi->UpdatePlayerGold(player.GetGoldForHUD());
		gi->UpdatePlayerHealth(player.GetHealthForHUD());

		gi->ClearText();
		gi->WriteLine(L"치유사 스칼드가 당신의 상처를 완벽하게 치유했습니다.");
		gi->WriteLine(L"체력이 최대치로 회복되었습니다!");
	}

	gi->WriteLine();
	gi->WriteLine(L"치유사 스칼드가 당신에게 따스한 미소를 건넵니다.");
	gi->WriteLine(L"당신의 앞날에 평온이 가득하기를");
	gi->WriteLine();
	gi->WriteLine(L"치유의 집을 나갑니다... ");
	gi->WriteLine(L"이제 어떻게 할까?");
	gi->WriteLine();
	gi->WriteLine(L"1. 마을로 돌아가기");
	gi->WriteLine(L"2. 타이틀로 돌아가기");
	gi->WriteLine();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&VillageLevel::ShowGreetingMenu, this)},
			{L"2", bind(&VillageLevel::OnExitVillage, this)},
		}
		);
}

void VillageLevel::OnExitVillage()
{
	gi->WriteLine();
	gi->WriteLine(L"마을을 떠납니다... ");
	gi->WriteLine(L"묵묵히 걸어가는 당신의 뒤를 누군가가 바라보고 있습니다..");
	gi->WriteLine();

	LevelManager::GetInstance()->SetNextLevel(L"Title");
	BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();

	InputSystem::Clear();
}
