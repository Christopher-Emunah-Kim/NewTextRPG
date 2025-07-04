#include "VillageLevel.h"
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
}

void VillageLevel::Init()
{
	constexpr int32 HEAL_COST = 100;
	m_healer = new Healer(HEAL_COST);

	m_merchant = new Merchant();
	m_merchant->AddSaleItem(13001);
	m_merchant->AddSaleItem(12001);
	m_merchant->AddSaleItem(23001);
	m_merchant->AddSaleItem(22001);

	gi = GameInstance::GetInstance();

	Welcome();

	BaseLevel::Init();
}

void VillageLevel::Welcome()
{
	GameInstance::GetInstance()->ClearText();
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
	gi->WriteLine(L"3. 마을을 떠난다.");
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
			Welcome();
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
			{L"2", bind(&VillageLevel::OnSellIItem, this)},
			{L"3", bind(&VillageLevel::Welcome, this)},
		}
		);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			Welcome();
		}
	);
}

void VillageLevel::OnBuyItem()
{
	ItemDataTable* itemDataTable = ItemDataTable::GetInstance();

	gi->WriteLine();
	gi->WriteLine(L"상점에서 판매하는 아이템 목록을 보여줍니다.");
	gi->WriteLine();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"[판매 중인 아이템 목록]");
	gi->WriteLine();
	gi->WriteLine(L"0: 뒤로가기");
	gi->WriteLine();

	
	vector<int32> salesItems = m_merchant->GetSalesItems();
	for (size_t index = 0; index < salesItems.size(); ++index)
	{
		const BaseItem* item = itemDataTable->GetItem(salesItems[index]);
		
		wstringstream ss;
		ss << index + 1 << L"." << item->GetName() <<
			L" - 가격: " << item->GetBuyingPrice() << L" 골드";

		if (itemDataTable->IsEquippable(item->GetItemID()))
		{
			ss << L" | " << item->GetAddableStatus().ToString();
		}

		gi->WriteLine(ss.str());
		gi->WriteLine(L"-> " + item->GetDescription());
	}

	if (salesItems.empty()) 
	{
		gi->WriteLine(L"현재 판매 중인 상품이 없습니다.");
	}

	gi->WriteLine(L"============================================");
	gi->WriteLine(L"구매할 아이템 번호를 입력하세요");

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
	const BaseItem* item = ItemDataTable::GetInstance()->GetItem(itemId);

	EMerchantResult result = m_merchant->SellItem(itemId, player);
	switch (result)
	{
	case EMerchantResult::NotEnoughGold:
	{
		gi->ClearText();
		gi->WriteLine(L"골드가 부족합니다.");
	}
	break;
	case EMerchantResult::Success:
	{
		gi->UpdatePlayerGold(player.GetGold());
		gi->UpdateEquippedItem(item->GetName(), item->GetItemType());

		gi->ClearText();
		gi->WriteLine(item->GetName() + L"을(를) 구매 후 장착했습니다!");
		gi->WriteLine(L"남은 골드: " + to_wstring(player.GetGoldAmount()));
	}
	break;

	default:
	{
		gi->ClearText();
		gi->WriteLine(L"아이템 구매에 실패했습니다.");
	}
	}

	gi->WriteLine();
	gi->WriteLine(L"1. 계속 쇼핑하기");
	gi->WriteLine(L"2. 상점 메뉴로 돌아가기");

	InputSystem::BindAction({
		{L"1", bind(&VillageLevel::OnBuyItem, this)},
		{L"2", bind(&VillageLevel::OnEnterItemShop, this)}
		});


}

void VillageLevel::OnSellIItem()
{
	Player& player = gi->GetPlayer();
	Inventory& inventory = player.GetInventory();

	gi->WriteLine();
	gi->WriteLine(L"상인에게 판매 가능한 아이템 목록을 보여줍니다.");
	gi->WriteLine();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"[판매 가능한 아이템 목록]");
	gi->WriteLine();
	gi->WriteLine(L"0: 뒤로가기");
	gi->WriteLine();

	const vector<BaseItem*>& items = inventory.GetInventoryItems();
	for (size_t index = 0; index < items.size(); ++index)
	{
		const BaseItem* item = items[index];

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

	InputSystem::BindAction(L"0", bind(&VillageLevel::OnEnterItemShop, this));
	for (size_t index = 0; index < items.size(); ++index)
	{
		InputSystem::BindAction(to_wstring(index + 1),
			bind(&VillageLevel::SellSelectedItem, this, items[index]->GetItemID()));
	}

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			OnSellIItem();
		}
	);
}

void VillageLevel::SellSelectedItem(int32 itemId)
{
	Player& player = gi->GetPlayer();
	const BaseItem* item = ItemDataTable::GetInstance()->GetItem(itemId);
	Inventory& inventory = player.GetInventory();

	bool result = m_merchant->BuyItem(itemId, player);

	if (result)
	{
		gi->ClearText();
		gi->WriteLine(L"상인은 흡족해하며 당신에게 받은 물품을 살펴봅니다.");
		inventory.RemoveItem(itemId);
		gi->UpdatePlayerGold(player.GetGold());
		gi->UpdateInvetoryItems(inventory.GetInventoryItems());
	}
	else
	{
		gi->WriteLine(L"현재 판매 가능한 아이템이 없습니다.");
		gi->WriteLine(L"던전에 가서 몹을 처치하세요.");
	}

	gi->WriteLine();
	gi->WriteLine(L"1. 계속 판매하기");
	gi->WriteLine(L"2. 상점 메뉴로 돌아가기");

	InputSystem::BindAction({
		{L"1", bind(&VillageLevel::OnSellIItem, this)},
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

	InputSystem::BindAction(
		{
			{L"1", bind(&VillageLevel::OnRecoverPlayer, this)},
			{L"2", bind(&VillageLevel::Welcome, this)},
		}
		);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			Welcome();
		}
	);
}

void VillageLevel::OnRecoverPlayer()
{
	Player& player = gi->GetPlayer();

	EHealResult result = m_healer->CheckHealAvailable(player);
	switch (result)	
	{
	case EHealResult::RequestAccept:
	{
		m_healer->Heal(player);
		gi->UpdatePlayerGold(player.GetGold());
		gi->UpdatePlayerHealth(player.GetHealth());

		gi->ClearText();
		gi->WriteLine(L"치유사 스칼드가 당신의 상처를 완벽하게 치유했습니다.");
		gi->WriteLine(L"체력이 최대치로 회복되었습니다!");
	}
		break;
	case EHealResult::NotEnoughGold:
	{
		gi->ClearText();
		gi->WriteLine(L"골드가 부족합니다. 치유를 받을 수 없습니다.");
		wstring costText = to_wstring(m_healer->GetHealCost());
		gi->WriteLine(L"필요 골드: " + costText + L", 보유 골드: " +
			to_wstring(player.GetGold().GetAmount()));
	}
		break;
	case EHealResult::AlreadyMaxHealth:
	{
		gi->ClearText();
		gi->WriteLine(L"치유사 스칼드가 당신을 살펴봅니다.");
		gi->WriteLine(L"이미 건강 상태가 완벽하시군요. 치유가 필요하지 않습니다.");
	}
		break;

	default:
	{
		throw invalid_argument("힐러의 집에서 디폴트 에러 발생. 조치 바람.");
	}
		break;
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
			{L"1", bind(&VillageLevel::Welcome, this)},
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
