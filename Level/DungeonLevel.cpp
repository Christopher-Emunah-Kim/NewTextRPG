#include "DungeonLevel.h"
#include "../Core/GameInstance.h"
#include "../Core/LevelManager.h"
#include "../Util/BattleSystem.h"
#include "../Util/InputSystem.h"
#include "../Object/Character/Monster.h"
#include "../Data/MonsterDataTable.h"

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
		gi->WriteLine(L"");
		gi->WriteLine(L"던전을 모두 탐험했습니다! ");
		gi->WriteLine(L"당신은 던전의 모든 몬스터를 처치하고 돌아갑니다.");
		gi->WriteLine(L"");
		gi->WriteLine(L"1. 이제 충분해. 던전 입구로 돌아가자.");
		gi->WriteLine(L"2. 이제 진짜 정말 충분해. 던전 입구로 돌아가자.");
		gi->WriteLine(L"");
		gi->WriteLine(L"============================================");
		gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

		//SetDungeonStage();

		InputSystem::BindAction(
			{
				{L"1", bind(&DungeonLevel::OnBackToVillage, this)},
				{L"2", bind(&DungeonLevel::OnBackToVillage, this)},
			}
			);
		return;
	}

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

	BattleSystem battleSystem;
	BattleResult result = battleSystem.ExecuteBattle(&player, m_currentMonster);

	for (size_t i = 0; i < result.battleMessages.size(); ++i)
	{
		gi->WriteLine(result.battleMessages[i]);
	}

	if (result.winner == &player)
	{
		DisplayVictoryRewards(result.rewards);
		OnMonsterDefeated();
	}
	else if (result.loser == &player)
	{
		DisplayDefeatScreen();

	}
	else
	{
		ContinueExploration();
	}

}

void DungeonLevel::DisplayVictoryRewards(const BattleRewardInfo& rewards)
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
		
	if (rewards.droppedItem)
	{
		gi->WriteLine(L"");
		gi->WriteLine(m_currentMonster->GetName() + L"에게서 " + rewards.droppedItem->GetName() + L"을(를) 획득했습니다!");

		if (rewards.bItemEquipped)
		{
			gi->WriteLine(rewards.droppedItem->GetName()+ L"을(를 장착했습니다.");
			gi->WriteLine(L"공격력: +" + to_wstring(rewards.droppedItem->GetAttack()) +
				L", 방어력: +" + to_wstring(rewards.droppedItem->GetDefense()) +
				L", 민첩성: +" + to_wstring(rewards.droppedItem->GetAgility()));
		}
		else if (rewards.bItemAddedToInventory)
		{
			gi->WriteLine(rewards.droppedItem->GetName() + L"을(를) 인벤토리에 넣었습니다.");
		}
		else
		{
			gi->WriteLine(L"인벤토리가 가득 차서 " + rewards.droppedItem->GetName() + L"을(를) 버렸습니다.");
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

void DungeonLevel::OnMonsterDefeated()
{
	--m_activeMonseters;

	ContinueExploration();
}

void DungeonLevel::OnEscape()
{
	gi->WriteLine(L"");
	gi->WriteLine(L"당신은 빠르게 몸을 돌려 던전 입구로 뛰어갑니다.");

	if (rand() % 3 == 0)
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

	InputSystem::Clear();
}
