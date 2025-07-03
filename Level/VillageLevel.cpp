#include "VillageLevel.h"
#include "../Core/GameInstance.h"
#include "../Core/LevelManager.h"
#include "../Util/InputSystem.h"
#include "../Item/BaseItem.h"
#include "Data/ItemDataTable.h"
#include "Component/Player/InventoryComp.h"
#include "Component/Player/PlayerStatusComp.h"
#include "Component/Player/EquipmentComp.h"

void VillageLevel::Init()
{
	gi = GameInstance::GetInstance();

	Welcome();
}

void VillageLevel::Welcome()
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
			gi->WriteLine(L"디버깅: '" + itemName + L"' 아이템을 찾을 수 없습니다.");
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

		gi->WriteLine(itemInfo);
		gi->WriteLine(L"   " + item->GetDescription());
		gi->WriteLine();
	}

	if (selectedItems.empty()) 
	{
		gi->WriteLine(L"현재 판매 중인 상품이 없습니다.");
	}

	gi->WriteLine(L"============================================");
	gi->WriteLine(L"구매할 아이템 번호를 입력하세요");

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
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			OnBuyItem();
		}
	);
}

void VillageLevel::BuySelectedItem(const wstring& itemName)
{
	const BaseItem* selectedItem = ItemDataTable::GetInstance()->GetItem(itemName);

	if (selectedItem)
	{
		Player& player = gi->GetPlayer();

		PlayerStatusComp* statusComp = player.GetComponentByType<PlayerStatusComp>();
		EquipmentComp* equipmentComp = player.GetComponentByType<EquipmentComp>();


		if (!statusComp || !equipmentComp)
		{
			gi->WriteLine(L"오류: 플레이어 컴포넌트를 찾을 수 없습니다.");
			return;
		}

		
		if (statusComp->UseGold(selectedItem->GetBuyingPrice()))
		{
			BaseItem* newItem = selectedItem->CreateItem();

			if (equipmentComp->EquipItem(newItem))
			{
				gi->ClearText();
				gi->WriteLine(selectedItem->GetName() + L"을(를) 구매 후 장착했습니다!");
				gi->WriteLine(L"남은 골드: " + to_wstring(statusComp->GetPlayerInfo().gold.GetAmount()));
			}
			else
			{
				statusComp->GainGold(selectedItem->GetBuyingPrice());
				delete newItem; 
				gi->ClearText();
				gi->WriteLine(L"아이템 장착에 실패했습니다.");
			}

		}
		else 
		{
			gi->ClearText();
			gi->WriteLine(L"골드가 부족합니다.");
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
}

void VillageLevel::OnEnterHealerShop()
{
	Player& player = gi->GetPlayer();

	gi->WriteLine();
	gi->WriteLine(L"치유의 집에 들어갑니다.");
	gi->WriteLine(L"치유사 스칼드 가 당신을 반깁니다.");
	gi->WriteLine();
	gi->WriteLine(L"반가워요. 당신이 바로 그..." + player.GetPlayerInfo().name + L" 용사군요.");
	gi->WriteLine();
	gi->WriteLine(L"치유사가 당신의 상태를 살펴봅니다.");

	gi->WriteLine();
	healerCost = HEALER_COST;
	wstring costText = to_wstring(healerCost);
	gi->WriteLine(L"1. 퍼펙트 힐링 요청하기(소모골드 : " + costText + L" )");
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

	PlayerStatusComp* statusComp = player.GetComponentByType<PlayerStatusComp>();
	if (!statusComp)
	{
		gi->ClearText();
		gi->WriteLine(L"오류: 플레이어 상태 정보를 찾을 수 없습니다.");
		OnEnterHealerShop();
		return;
	}
	int32 healAmount = player.GetPlayerInfo().maxHealth - player.GetPlayerInfo().health;

	if (healAmount <= 0)
	{
		gi->ClearText();
		gi->WriteLine(L"치유사 스칼드가 당신을 살펴봅니다.");
		gi->WriteLine(L"이미 건강 상태가 완벽하시군요. 치유가 필요하지 않습니다.");
	}
	else
	{
		healerCost = HEALER_COST;
		if (statusComp->UseGold(healerCost))
		{
			statusComp->RecoverHealth(healAmount);

			gi->ClearText();
			gi->WriteLine(L"치유사 스칼드가 당신의 상처를 완벽하게 치유했습니다.");
			gi->WriteLine(L"체력이 " + to_wstring(healAmount) + L"회복됩니다.");
			gi->WriteLine(L"체력이 최대치로 회복되었습니다!");
			gi->WriteLine(L"남은 골드: " + to_wstring(statusComp->GetPlayerInfo().gold.GetAmount()));
		}
		else
		{
			gi->ClearText();
			gi->WriteLine(L"골드가 부족합니다. 치유를 받을 수 없습니다.");
			wstring costText = to_wstring(healerCost);
			gi->WriteLine(L"필요 골드: " + costText + L", 보유 골드: " +
				to_wstring(statusComp->GetPlayerInfo().gold.GetAmount()));
		}
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
