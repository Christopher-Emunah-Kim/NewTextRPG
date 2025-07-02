#include "VillageLevel.h"
#include "../Core/GameInstance.h"
#include "../Util/InputSystem.h"
#include "Data/ItemDataTable.h"
#include "../Item/BaseItem.h"
#include "Component/Player/InventoryComp.h"
#include "Component/Player/PlayerStatusComp.h"

void VillageLevel::Init()
{
	SetVillageStage();
	Welcome();
	BaseLevel::Init();
}

void VillageLevel::Release()
{
}

void VillageLevel::SetVillageStage()
{
}

void VillageLevel::Welcome()
{
	GameInstance* gameInstance = GameInstance::GetInstance();
	gameInstance->ClearText();

	gameInstance->EnqueueText(L"============================================");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"당신은 마을에 도착했습니다.");
	gameInstance->EnqueueText(L"마을은 평화롭고 안전해 보입니다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"마을에서 무엇을 하시겠습니까?");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"[마을 메뉴 옵션]");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"1. 아이템 상점에 들어간다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"2. 치유사의 집에 들어간다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"3. 마을을 떠난다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"============================================");
	gameInstance->EnqueueText(L"원하는 옵션의 번호를 입력하세요.");

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
			GameInstance::GetInstance()->ClearText();
			GameInstance::GetInstance()->EnqueueText(L"잘못된 입력입니다. 다시 시도하세요.");
			Welcome();
		}
	);
}

void VillageLevel::OnEnterItemShop()
{
	GameInstance* gameInstance = GameInstance::GetInstance();

	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"상점에 들어갑니다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"상점 주인이 당신을 반깁니다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"상점에서 아이템을 구매하거나 판매할 수 있습니다.");
	gameInstance->EnqueueText(L"상점에서 무엇을 하시겠습니까?");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"1. 아이템 구매하기");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"2. 아이템 판매하기");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"3. 상점에서 나가기");
	gameInstance->EnqueueText(L"");

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
			GameInstance::GetInstance()->ClearText();
			GameInstance::GetInstance()->EnqueueText(L"잘못된 입력입니다. 다시 시도하세요.");
			Welcome();
		}
	);
}

void VillageLevel::OnBuyItem()
{
	GameInstance* gameInstance = GameInstance::GetInstance();
	ItemDataTable* itemDataTable = ItemDataTable::GetInstance();

	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"상점에서 판매하는 아이템 목록을 보여줍니다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"============================================");
	gameInstance->EnqueueText(L"[판매 중인 아이템 목록]");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"0: 뒤로가기");
	gameInstance->EnqueueText(L"");

	//DEBUG
	//vector<wstring> availableItems = itemDataTable->GetItemNames();
	//gameInstance->EnqueueText(L"디버깅: 총 " + to_wstring(availableItems.size()) + L"개의 아이템이 데이터베이스에 있습니다.");

	vector<wstring> selectedItemNames = 
	{
		L"묵직한 대검",
		L"신속한 단검",
		L"강철 갑옷",
		L"경량 갑옷"
	};

	vector<const BaseItem*> selectedItems;

	for (size_t i = 0; i < selectedItemNames.size(); ++i)
	{
		const wstring& itemName = selectedItemNames[i];
		const BaseItem* item = itemDataTable->GetItem(itemName);
		if (item) 
		{
			selectedItems.push_back(item);
		}
		else
		{
			gameInstance->EnqueueText(L"디버깅: '" + itemName + L"' 아이템을 찾을 수 없습니다.");
		}
	}

	for (int i = 0; i < selectedItems.size(); ++i) 
	{
		const BaseItem* item = selectedItems[i];

		wstring itemInfo = to_wstring(i + 1) + L". " + item->GetName();
		itemInfo += L" - 가격: " + to_wstring(item->GetBuyingPrice()) +	L" 골드";

		if (item->GetItemType() == EItemType::Weapon || item->GetItemType() == EItemType::Armor) 
		{
			itemInfo += L" | 공격력: " + to_wstring(item->GetAttack()) +
				L", 방어력: " + to_wstring(item->GetDefense()) +
				L", 민첩성: " + to_wstring(item->GetAgility());
		}

		gameInstance->EnqueueText(itemInfo);
		gameInstance->EnqueueText(L"   " + item->GetDescription());
		gameInstance->EnqueueText(L"");
	}

	if (selectedItems.empty()) 
	{
		gameInstance->EnqueueText(L"현재 판매 중인 상품이 없습니다.");
	}

	gameInstance->EnqueueText(L"============================================");
	gameInstance->EnqueueText(L"구매할 아이템 번호를 입력하세요");

	InputSystem::BindAction(
		{
			{L"0", bind(&VillageLevel::OnEnterItemShop, this)},
			{L"1", [this, selectedItemNames]() { this->BuySelectedItem(selectedItemNames[0]); }},
			{L"2", [this, selectedItemNames]() { this->BuySelectedItem(selectedItemNames[1]); }},
			{L"3", [this, selectedItemNames]() { this->BuySelectedItem(selectedItemNames[2]); }},
			{L"4", [this, selectedItemNames]() { this->BuySelectedItem(selectedItemNames[3]); }},
		}
		);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			GameInstance::GetInstance()->ClearText();
			GameInstance::GetInstance()->EnqueueText(L"잘못된 입력입니다. 다시 시도하세요.");
			OnBuyItem();
		}
	);
}

void VillageLevel::BuySelectedItem(const wstring& itemName)
{
	GameInstance* gameInstance = GameInstance::GetInstance();
	const BaseItem* selectedItem = ItemDataTable::GetInstance()->GetItem(itemName);

	if (selectedItem)
	{
		Player& player = gameInstance->GetPlayer();

		PlayerStatusComp* statusComp = player.GetComponentByType<PlayerStatusComp>();
		InventoryComp* inventoryComp = player.GetComponentByType<InventoryComp>();


		if (!statusComp || !inventoryComp) 
		{
			gameInstance->EnqueueText(L"오류: 플레이어 컴포넌트를 찾을 수 없습니다.");
			return;
		}

		
		if (statusComp->UseGold(selectedItem->GetBuyingPrice()))
		{
			
			bool bIsItemAdded = inventoryComp->AddItem(itemName, 1);

			if (bIsItemAdded) 
			{
				gameInstance->ClearText();
				gameInstance->EnqueueText(selectedItem->GetName() + L"을(를) 구매했습니다!");
				gameInstance->EnqueueText(L"남은 골드: " + to_wstring(statusComp->GetPlayerInfo().gold.GetAmount()));
			}
			else 
			{
				statusComp->GainGold(selectedItem->GetBuyingPrice());
				gameInstance->ClearText();
				gameInstance->EnqueueText(L"인벤토리가 가득 찼습니다.");
			}
		}
		else 
		{
			gameInstance->ClearText();
			gameInstance->EnqueueText(L"골드가 부족합니다.");
		}
	}

	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"1. 계속 쇼핑하기");
	gameInstance->EnqueueText(L"2. 상점 메뉴로 돌아가기");

	InputSystem::BindAction({
		{L"1", bind(&VillageLevel::OnBuyItem, this)},
		{L"2", bind(&VillageLevel::OnEnterItemShop, this)}
		});


}

void VillageLevel::OnSellIItem()
{
}

void VillageLevel::OnEnterHealerShop()
{
}

void VillageLevel::OnExitVillage()
{
}
