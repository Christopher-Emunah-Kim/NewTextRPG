#include "DungeonLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/UI/HUD.h"
#include "../Screen.h"
#include "../Util/InputSystem.h"
#include "../Manager/LevelManager.h"
#include "../Object/Character/Monster.h"
#include "../Component/Player/PlayerStatusComp.h"



void DungeonLevel::Init()
{
	SetDungeonStage();

	Welcome();

	BaseLevel::Init();
}


void DungeonLevel::Release()
{
	delete m_monster;
	m_monster = nullptr;
}


void DungeonLevel::SetDungeonStage()
{
	if (m_monster)
	{
		delete m_monster;
		m_monster = nullptr;
	}

	FMonsterInfo customInfo(1);
	customInfo.health = 15;
	customInfo.maxHealth = 15;
	customInfo.status = Status::NewStatus(8, 10, 20);
	m_monster = new Monster(this, L"허약한 고블린", customInfo);

}

void DungeonLevel::Welcome()
{
	GameInstance* gameInstance = GameInstance::GetInstance();
	gameInstance->ClearText();

	gameInstance->EnqueueText(L"============================================");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"당신은 동굴 입구 앞에 섰습니다.");
	gameInstance->EnqueueText(L"으스스한 동굴이 당신을 반깁니다..");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"도전하시겠습니까?");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"[던전 메뉴 옵션]");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"1. 인생은 모험이지! 도전한다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"2. 지금은 아닌것 같아.. 마을로 돌아갈래");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"============================================");
	gameInstance->EnqueueText(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::OnEnterStage, this)},
			{L"2", bind(&DungeonLevel::OnBackToVillage, this)},
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

void DungeonLevel::OnEnterStage()
{
	GameInstance* gameInstance = GameInstance::GetInstance();

	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"던전에 입장합니다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"당신의 눈 앞에 " + m_monster->GetName() + L"가(이) 등장했습니다!");
	gameInstance->EnqueueText(L"상대는 아직 당신을 눈치채지 못했습니다.");
	gameInstance->EnqueueText(L"전투를 시작할까요?");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"1. 지금이 기회다. 빠르게 적에게 달려간다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"2. 지금은 상태가 좋지않아. 던전 입구로 돌아간다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"============================================");
	gameInstance->EnqueueText(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::OnStartBattle, this)},
			{L"2", bind(&DungeonLevel::OnEscape, this)},
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

void DungeonLevel::OnBackToVillage()
{
	GameInstance::GetInstance()->EnqueueText(L"");
	GameInstance::GetInstance()->EnqueueText(L"때로는 한발 물러서는 것이 현명할 수 있습니다....");
	GameInstance::GetInstance()->EnqueueText(L"당신은 발걸음을 돌려 마을로 돌아갑니다...");

	InputSystem::Clear();
}

void DungeonLevel::OnStartBattle()
{
	Player& player = GameInstance::GetInstance()->GetPlayer();
	

	player.Interact(m_monster);

}

void DungeonLevel::OnEscape()
{
	GameInstance::GetInstance()->EnqueueText(L"");
	GameInstance::GetInstance()->EnqueueText(L"당신은 빠르게 몸을 돌려 던전 입구로 뛰어갑니다.");

	if (rand() % 3 == 0)
	{
		GameInstance::GetInstance()->EnqueueText(L"필사적으로 뛰었지만, "+ m_monster->GetName() + L"가(이) 먼저 당신의 앞을 가로 막았습니다.");
		GameInstance::GetInstance()->EnqueueText(m_monster->GetName() + L"가(이) 당신을 공격합니다..");
		//TODO : 몬스터 공격턴 
	}
	else
	{
		GameInstance::GetInstance()->EnqueueText(L"몬스터가 당신을 쫓아왔지만, 당신은 무사히 던전 입구로 도망쳤습니다.");
		Welcome();
	}

	InputSystem::Clear();
}
