#include "DungeonLevel.h"
#include "../Core/GameInstance.h"
#include "../Core/LevelManager.h"
#include "../Data/MonsterDataTable.h"
#include "Data/ItemDataTable.h"
#include "../Util/BattleSystem.h"
#include "../Util/InputSystem.h"
#include "../Object/Character/Monster.h"
#include "Item/InventoryItem.h"
#include "Item/BaseItem.h"

void DungeonLevel::Init()
{
	gi = GameInstance::GetInstance();

	SetDungeonStage();
	Welcome();

	BaseLevel::Init();
}


void DungeonLevel::Release()
{
	if (m_currentMonster)
	{
		delete m_currentMonster;
		m_currentMonster = nullptr;
	}
}


void DungeonLevel::SetDungeonStage()
{
	MonsterDataTable* monsterDataTable = MonsterDataTable::GetInstance();
	m_monsterNames = monsterDataTable->GetMonsterNames();

	if (m_monsterNames.empty())
	{
		gi->WriteLine(L"몬스터 데이터가 비어있습니다. 던전 레벨을 초기화할 수 없어 임의로 몬스터를 추가합니다.");
		m_monsterNames.push_back(L"허약한 고블린");
		m_monsterNames.push_back(L"불쌍한 오크");
		m_monsterNames.push_back(L"강맹한 늑대");
	}

	m_activeMonseters = m_maxMonsters;
}

void DungeonLevel::CreateRandomMonster()
{
	if (!m_monsterNames.empty())
	{
		int randomIndex = rand() % m_monsterNames.size();
		wstring monsterName = m_monsterNames[randomIndex];

		MonsterDataTable* monsterDataTable = MonsterDataTable::GetInstance();
		m_currentMonster = monsterDataTable->CreateMonster(this, monsterName);

		if (m_currentMonster == nullptr) 
		{
			FMonsterInfo customInfo(1);
			customInfo.health.New(15);
			customInfo.status = Status::NewStatus(8, 10, 20);
			m_currentMonster = new Monster(this, L"허약한 고블린", customInfo);
		}
	}
}

void DungeonLevel::Welcome()
{

	gi->ClearText();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(L"당신은 동굴 입구 앞에 섰습니다.");
	gi->WriteLine(L"으스스한 동굴이 당신을 반깁니다..");
	gi->WriteLine(L"");
	gi->WriteLine(L"도전하시겠습니까?");
	gi->WriteLine(L"");
	gi->WriteLine(L"[던전 메뉴 옵션]");
	gi->WriteLine(L"");
	gi->WriteLine(L"1. 인생은 모험이지! 도전한다.");
	gi->WriteLine(L"");
	gi->WriteLine(L"2. 지금은 아닌것 같아.. 마을로 돌아갈래");
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::OnEnterStage, this)},
			{L"2", bind(&DungeonLevel::OnBackToVillage, this)},
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

void DungeonLevel::ContinueExploration()
{
	if (m_activeMonseters <= 0)
	{
		gi->ClearText();
		gi->WriteLine(L"============================================");
		gi->WriteLine(L"");
		gi->WriteLine(L"던전을 모두 탐험했습니다! ");
		gi->WriteLine(L"당신은 던전의 모든 몬스터를 처치하고 돌아갑니다.");
		gi->WriteLine(L"");
		gi->WriteLine(L"1. 이제 충분해. 던전 입구로 돌아가자.");
		gi->WriteLine(L"2. 이제 진짜 정말 충분해. 던전 입구로 돌아가자.");
		gi->WriteLine(L"");
		gi->WriteLine(L"============================================");
		gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");


		InputSystem::BindAction(
			{
				{L"1", bind(&DungeonLevel::OnBackToVillage, this)},
				{L"2", bind(&DungeonLevel::OnBackToVillage, this)},
			}
			);
		return;
	}

	gi->ClearText();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(L"당신은 던전을 더 탐험할 수 있습니다. 앞으로 나아갈까요?");
	wstring activeMonster = to_wstring(m_activeMonseters);
	gi->WriteLine(L"남은 몬스터: " + activeMonster + L"마리");
	gi->WriteLine(L"");
	gi->WriteLine(L"1. 계속해서 던전을 탐험한다.");
	gi->WriteLine(L"");
	gi->WriteLine(L"2. 지금은 충분해. 던전 입구로 돌아간다.");
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::OnEnterStage, this)},
			{L"2", bind(&DungeonLevel::Welcome, this)},
		}
		);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			ContinueExploration();
		}
	);
}

void DungeonLevel::OnEnterStage()
{
	CreateRandomMonster();
	if (m_currentMonster == nullptr)
	{
		gi->WriteLine(L"몬스터를 생성할 수 없습니다. 초기화면으로 돌아갑니다..");
		Welcome();
		return;
	}

	gi->ClearText();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(L"던전에 입장합니다.");
	gi->WriteLine(L"");
	gi->WriteLine(L"당신의 눈 앞에 " + m_currentMonster->GetName() + L"가(이) 등장했습니다!");
	gi->WriteLine(L"상대는 아직 당신을 눈치채지 못했습니다.");
	gi->WriteLine(L"전투를 시작할까요?");
	gi->WriteLine(L"");
	gi->WriteLine(L"1. 지금이 기회다. 빠르게 적에게 달려간다.");
	gi->WriteLine(L"");
	gi->WriteLine(L"2. 지금은 상태가 좋지않아. 던전 입구로 돌아간다.");
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::OnStartBattle, this)},
			{L"2", bind(&DungeonLevel::OnEscape, this)},
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

void DungeonLevel::OnBackToVillage()
{
	gi->WriteLine(L"");
	gi->WriteLine(L"때로는 한발 물러서는 것이 현명할 수 있습니다....");
	gi->WriteLine(L"당신은 발걸음을 돌려 마을로 돌아갑니다...");

	LevelManager::GetInstance()->SetNextLevel(L"Village");
	BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();

	InputSystem::Clear();
}

void DungeonLevel::OnStartBattle()
{
	Player& player = gi->GetPlayer();
	vector<wstring> battleStartMessges;

	gi->ClearText();
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(L"전투가 시작됩니다!");
	gi->WriteLine(L"");
	gi->WriteLine(player.GetName() + L"와(과) " + m_currentMonster->GetName() + L"가(이) 전투를 시작합니다!");
	gi->WriteLine(L"");

	bool bIsPlayerFirst = BattleSystem::DetermineFirstAttacker(&player, m_currentMonster);

	if (bIsPlayerFirst)
	{
		gi->WriteLine(player.GetName() + L"가(이) 먼저 공격을 시도합니다.");
		ProcessPlayerTurn();
	}
	else
	{
		gi->WriteLine(m_currentMonster->GetName() + L"가(이) 먼저 공격을 시도합니다.");
		ProcessMonsterTurn();
	}
}

void DungeonLevel::ProcessPlayerTurn()
{
	Player& player = gi->GetPlayer();

	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(L"[현재 상태]");
	gi->WriteLine(L"당신의 체력: " + to_wstring(player.GetBattleCharacterInfo().health.GetCurrentAmount()) + L"/" + to_wstring(player.GetBattleCharacterInfo().health.GetMaxAmount()));
	gi->WriteLine(m_currentMonster->GetName() + L"의 체력: " + to_wstring(m_currentMonster->GetBattleCharacterInfo().health.GetCurrentAmount()) 
		+ L"/" + to_wstring(m_currentMonster->GetBattleCharacterInfo().health.GetMaxAmount()));
	gi->WriteLine(L"");
	gi->WriteLine(L"당신은 거친 숨을 몰아쉬며 적을 노려봅니다.");
	gi->WriteLine(L"");
	gi->WriteLine(L"1. 물러날 곳은 없다. 지체없이 공격하자.");
	gi->WriteLine(L"2. 필요한 아이템을 사용한다.");
	gi->WriteLine(L"3. 물러날 때이다. 던전 입구로 도망가자");
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::ProcessPlayerAttack, this)},
			{L"2", bind(&DungeonLevel::OnShowUsuableItems, this)},
			{L"3", bind(&DungeonLevel::OnTryEscape, this)}
		}
	);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			ProcessPlayerTurn();
		}
	);

}

void DungeonLevel::ProcessMonsterTurn()
{
	Player& player = gi->GetPlayer();
	vector<wstring> battleMessages;

	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(L"[몬스터 턴]");
	gi->WriteLine(m_currentMonster->GetName() + L"가(이) 공격합니다!");

	int32 calculatedDamage = m_currentMonster->GetBattleCharacterInfo().status.CalculateDamage(m_currentMonster->GetBattleCharacterInfo().status, player.GetBattleCharacterInfo().status);
	gi->WriteLine(player.GetName() + L"가(이) " + to_wstring(calculatedDamage) + L" 의 피해를 입었습니다.");

	bool playerDefeated = BattleSystem::ExecuteAttack(m_currentMonster, &player);

	gi->WriteLine(player.GetName() + L"의 현재 체력: " + to_wstring(player.GetBattleCharacterInfo().health.GetCurrentAmount()));

	if (playerDefeated)
	{
		gi->WriteLine(L"");
		gi->WriteLine(player.GetName() + L"가(이) 쓰러졌습니다!");
		DisplayDefeatScreen();
		return;
	}

	ProcessPlayerTurn();
}

void DungeonLevel::ProcessPlayerAttack()
{
	Player& player = gi->GetPlayer();

	gi->ClearText();
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(L"[플레이어 턴]");
	gi->WriteLine(player.GetName() + L"가(이) " + m_currentMonster->GetName() + L"을(를) 공격합니다!");

	int32 calculatedDamage = player.GetBattleCharacterInfo().status.CalculateDamage(player.GetBattleCharacterInfo().status, m_currentMonster->GetBattleCharacterInfo().status);
	gi->WriteLine(m_currentMonster->GetName() + L"가(이) " + to_wstring(calculatedDamage) + L" 의 피해를 입었습니다.");

	bool monsterDefeated = BattleSystem::ExecuteAttack(&player, m_currentMonster);
	gi->UpdatePlayerHealth(player.GetBattleCharacterInfo().health);

	gi->WriteLine(m_currentMonster->GetName() + L"의 현재 체력: " + to_wstring(m_currentMonster->GetBattleCharacterInfo().health.GetCurrentAmount()));


	if (monsterDefeated)
	{
		ProcessBattleResult(true);
		return;
	}

	ProcessMonsterTurn();
}

void DungeonLevel::OnShowUsuableItems()
{
	Player& player = gi->GetPlayer();

	gi->WriteLine();
	gi->WriteLine(L"사용 가능한 아이템 목록을 보여줍니다.");
	gi->WriteLine();
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(L"[사용 가능한 아이템 목록]");
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
			L" - 개수: " << item->GetCount();

		gi->WriteLine(ss.str());
		gi->WriteLine(L"-> " + item->GetDescription());
	}

	if (items.empty())
	{
		gi->WriteLine(L"현재 사용 가능한 아이템이 없습니다.");
	}

	gi->WriteLine(L"============================================");
	gi->WriteLine(L"사용할 아이템 번호를 입력하세요");

	InputSystem::BindAction(L"0", bind(&DungeonLevel::ProcessPlayerTurn, this));
	for (size_t index = 0; index < items.size(); ++index)
	{
		InputSystem::BindAction(to_wstring(index + 1),
			bind(&DungeonLevel::OnUseSelectedItem, this, items[index].GetItemId()));
	}

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			OnShowUsuableItems();
		}
	);
}

void DungeonLevel::OnUseSelectedItem(int32 itemId)
{
	Player& player = gi->GetPlayer();
	InventoryItem item = player.GetItemFromInventory(itemId);

	EItemType targetType = ItemDataTable::GetInstance()->GetItem(itemId)->GetItemType();
	int32 equippedItemId = player.GetEquippedItem(targetType);

	if (equippedItemId == -1)
	{
		gi->WriteLine(L"장착 중인 아이템이 존재하지 않습니다");
		return;
	}


	EPlayerHandleItemResult result = player.HandleOwnedItem(move(item));

	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine(GetMsgForItemHandleResult(result, move(item)));
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"");
	gi->WriteLine();
	gi->WriteLine(L"1. 다른 아이템 사용하기");
	gi->WriteLine(L"2. 전투로 돌아가기");

	if (result == EPlayerHandleItemResult::Equipped )
	{
		const BaseItem* targetItem = ItemDataTable::GetInstance()->GetItem(item.GetItemId());
		gi->UpdateEquippedItem(targetItem->GetName(), targetItem->GetItemType());

		player.RemoveItemFromInventory(itemId);
		player.AddItemToInventory(itemId);
		gi->UpdateInvetoryItems(player.GetInventoryItems());
	}
	else if (result == EPlayerHandleItemResult::UseItem)
	{
		player.RemoveItemFromInventory(itemId);
		gi->UpdateInvetoryItems(player.GetInventoryItems());
	}

	gi->UpdatePlayerStatus(player.GetTotalPlayerStatus());
	gi->UpdatePlayerHealth(player.GetHealthForHUD());


	InputSystem::BindAction({
		{L"1", bind(&DungeonLevel::OnShowUsuableItems, this)},
		{L"2", bind(&DungeonLevel::ProcessPlayerTurn, this)}
		});
}

wstring DungeonLevel::GetMsgForItemHandleResult(EPlayerHandleItemResult result, InventoryItem item)
{
	switch (result)
	{
	case EPlayerHandleItemResult::Equipped:
	{
		return ItemDataTable::GetInstance()->GetItem(item.GetItemId())->GetName() + L"을(를) 장착했습니다!";
	}
	break;
	case EPlayerHandleItemResult::UseItem:
	{
		return ItemDataTable::GetInstance()->GetItem(item.GetItemId())->GetName() + L"을(를) 사용하여 체력이 20 회복되었습니다!";
	}
	break;

	case EPlayerHandleItemResult::NotUsuableItem:
	{
		return L"사용할 수 없는 아이템입니다.";
	}
	break;

	case EPlayerHandleItemResult::ItemNullPtr:
	{
		return L"존재하지 않는 아이템입니다.";
	}

	default:
	{
		return L"아이템 처리 중 오류가 발생했습니다.";
	}
	break;
	}
}

void DungeonLevel::OnTryEscape()
{

	Player& player = gi->GetPlayer();

	gi->WriteLine(L"");
	gi->WriteLine(player.GetName() + L"가(이) 도망가려고 시도합니다...");

	if (BattleSystem::CanEscape(&player, m_currentMonster))
	{
		gi->WriteLine(L"도망치는데 성공했습니다!");
		OnEscape();
	}
	else
	{
		gi->WriteLine(L"도망치는데 실패했습니다!");
		gi->WriteLine(m_currentMonster->GetName() + L"가(이) 당신의 허점을 노립니다!");
		ProcessMonsterTurn();
	}
}

void DungeonLevel::ProcessBattleResult(bool monsterDefeated)
{
	if (monsterDefeated)
	{
		Player& player = gi->GetPlayer();
		FBattleResult result;
		result.winner = &player;
		result.loser = m_currentMonster;

		BattleSystem::HandleBattleRewards(&player, m_currentMonster, result);


		gi->WriteLine(L"");
		gi->WriteLine(m_currentMonster->GetName() + L"를(을) 처치했습니다!");

		DisplayVictoryRewards(result.rewards);

		gi->UpdatePlayerExperience(player.GetExperienceForHUD());
		gi->UpdatePlayerGold(player.GetGoldForHUD());
		if (result.rewards.bLevelUp)
		{
			gi->UpdatePlayerLevel(player.GetBattleCharacterInfo().characterLevel);
		}
		
		if (result.rewards.droppedItemId != -1)
		{
			if (result.rewards.bItemEquipped)
			{
				const BaseItem* targetItem = ItemDataTable::GetInstance()->GetItem(result.rewards.droppedItemId);
				gi->UpdateEquippedItem(targetItem->GetName(), targetItem->GetItemType());
				gi->UpdatePlayerStatus(player.GetTotalPlayerStatus());
			}
		}
		
		const vector<InventoryItem>& inventoryItems = player.GetInventoryItems();
        if (!inventoryItems.empty())
		{
			gi->UpdateInvetoryItems(inventoryItems);
		}

		MonsterDefeated();
	}
	else
	{
		gi->WriteLine(L"");
		gi->WriteLine(L"당신은 " + m_currentMonster->GetName() + L"에게 패배했습니다!");
		DisplayDefeatScreen();
	}
}

void DungeonLevel::DisplayVictoryRewards(const FBattleRewardInfo& rewards)
{
	if (rewards.expReward > 0)
	{
		gi->WriteLine(L"경험치 " + to_wstring(rewards.expReward) + L"을(를) 획득했습니다!");
		
		if (rewards.bLevelUp)
		{
			gi->WriteLine(L"레벨업! 능력치가 상승합니다.");
		}
	}

	if (rewards.goldReward > 0)
	{
		gi->WriteLine(L"골드 " + to_wstring(rewards.goldReward) + L"을(를) 획득했습니다!");
	}
		
	if (rewards.droppedItemId != -1)
	{
		const wstring itemName = ItemDataTable::GetInstance()->GetItem(rewards.droppedItemId)->GetName();
		gi->WriteLine(L"");
		gi->WriteLine(m_currentMonster->GetName() + L"에게서 ");
		gi->WriteLine(itemName + L"을(를) 획득했습니다!");

		if (rewards.bItemEquipped)
		{
			const BaseItem* targetItem = ItemDataTable::GetInstance()->GetItem(rewards.droppedItemId);
			gi->WriteLine(itemName + L"을(를) 장착했습니다.");
			gi->WriteLine(L"공격력: +" + to_wstring(targetItem->GetAttack()) +
				L", 방어력: +" + to_wstring(targetItem->GetDefense()) +
				L", 민첩성: +" + to_wstring(targetItem->GetAgility()));
			gi->WriteLine(L"");
		}
		else if (rewards.bItemAddedToInventory)
		{
			gi->WriteLine(itemName + L"을(를) 인벤토리에 넣었습니다.");
		}
		else
		{
			gi->WriteLine(L"인벤토리가 가득 차서 " + itemName + L"을(를) 버렸습니다.");
		}
	}
}

void DungeonLevel::DisplayDefeatScreen()
{
	gi->WriteLine(L"");
	gi->WriteLine(L"당신은 전투에서 패배했습니다...");
	gi->WriteLine(L"");
	gi->WriteLine(L"1. 마을로 돌아가자...");
	gi->WriteLine(L"2. 마을로...이제... 돌아가자...");
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::OnBackToVillage, this)},
			{L"2", bind(&DungeonLevel::OnBackToVillage, this)},
		}
		);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			gi->ClearText();
			gi->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			DisplayDefeatScreen();
		}
	);
}

void DungeonLevel::MonsterDefeated()
{
	--m_activeMonseters;

	ContinueExploration();
}

void DungeonLevel::OnEscape()
{
	gi->WriteLine(L"");
	gi->WriteLine(L"당신은 빠르게 몸을 돌려 던전 입구로 뛰어갑니다.");

	if (rand() % 2 == 0)
	{
		gi->WriteLine(L"필사적으로 뛰었지만, "+ m_currentMonster->GetName() + L"가(이) 먼저 당신의 앞을 가로 막았습니다.");
		gi->WriteLine(m_currentMonster->GetName() + L"가(이) 당신을 공격합니다..");
		
		OnStartBattle();
	}
	else
	{
		gi->WriteLine(L"몬스터가 당신을 쫓아왔지만, 당신은 무사히 던전 입구로 도망쳤습니다.");
		Welcome();
	}

}
