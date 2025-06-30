#include "DungeonLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/UI/HUDUI.h"
#include "../Screen.h"
#include "../Util/InputSystem.h"
#include "../Manager/LevelManager.h"
#include "../Object/Character/Monster.h"


DungeonLevel::DungeonLevel(const wstring& tag)
	:BaseLevel(tag), m_HUDUI(new HUDUI(this))
{
}

void DungeonLevel::Init()
{
	SetDungeonStage();

	Welcome();

	BaseLevel::Init();
}

void DungeonLevel::Render(Screen* screen)
{
	m_HUDUI->ClearSystemText();

	for (size_t line = 0; line < m_systemTexts.size(); ++line)
	{
		m_HUDUI->EnqueueText(m_systemTexts[line]);
	}

	BaseLevel::Render(screen);
}

void DungeonLevel::Release()
{
	delete m_HUDUI;
	m_HUDUI = nullptr;
	GameInstance::GetInstance()->SetHUDUI(nullptr);

	delete m_monster;
	m_monster = nullptr;
}


void DungeonLevel::SetDungeonStage()
{
	GameInstance* gameInstance = GameInstance::GetInstance();

	//m_HUDUI = new HUDUI(this);
	m_HUDUI->Init();
	gameInstance->SetHUDUI(m_HUDUI);

	m_monster = new Monster(this, L"Goblin");

}

void DungeonLevel::Welcome()
{
	ClearText();

	AddText(L"============================================");
	AddText(L"");
	AddText(L"당신은 동굴 입구 앞에 섰습니다.");
	AddText(L"으스스한 동굴이 당신을 반깁니다..");
	AddText(L"");
	AddText(L"도전하시겠습니까?");
	AddText(L"");
	AddText(L"[던전 메뉴 옵션]");
	AddText(L"");
	AddText(L"1. 인생은 모험이지! 도전한다.");
	AddText(L"");
	AddText(L"2. 지금은 아닌것 같아.. 마을로 돌아갈래");
	AddText(L"");
	AddText(L"============================================");
	AddText(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::OnEnterStage, this)},
			{L"2", bind(&DungeonLevel::OnBackToVillage, this)},
		}
	);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			ClearText();
			AddText(L"잘못된 입력입니다. 다시 시도하세요.");
			Welcome();
		}
	);
}

void DungeonLevel::OnEnterStage()
{
	AddText(L"");
	AddText(L"던전에 입장합니다.");
	AddText(L"");

	AddText(L"당신의 눈 앞에 " + m_monster->GetName() + L"가(이) 등장했습니다!");
	AddText(L"상대는 아직 당신을 눈치채지 못했습니다.");
	AddText(L"전투를 시작할까요?");

	AddText(L"");
	AddText(L"1. 지금이 기회다. 빠르게 적에게 달려간다.");
	AddText(L"");
	AddText(L"2. 지금은 상태가 좋지않아. 던전 입구로 돌아간다.");
	AddText(L"");
	AddText(L"============================================");
	AddText(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::OnStartBattle, this)},
			{L"2", bind(&DungeonLevel::OnEscape, this)},
		}
		);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			ClearText();
			AddText(L"잘못된 입력입니다. 다시 시도하세요.");
			Welcome();
		}
	);

	InputSystem::Clear();
}

void DungeonLevel::OnBackToVillage()
{
	AddText(L"");
	AddText(L"때로는 한발 물러서는 것이 현명할 수 있습니다....");
	AddText(L"당신은 발걸음을 돌려 마을로 돌아갑니다...");

	InputSystem::Clear();
}

void DungeonLevel::OnStartBattle()
{
	Player& player = GameInstance::GetInstance()->GetPlayer();

	player.Interact(m_monster);

}

void DungeonLevel::OnEscape()
{
	AddText(L"");
	AddText(L"당신은 빠르게 몸을 돌려 던전 입구로 뛰어갑니다.");

	if (rand() % 3 == 0)
	{
		AddText(L"필사적으로 뛰었지만, "+ m_monster->GetName() + L"가(이) 먼저 당신의 앞을 가로 막았습니다.");
		AddText(m_monster->GetName() + L"가(이) 당신을 공격합니다..");
		//TODO : 몬스터 공격턴 
	}
	else
	{
		AddText(L"몬스터가 당신을 쫓아왔지만, 당신은 무사히 던전 입구로 도망쳤습니다.");
		Welcome();
	}

	InputSystem::Clear();
}



void DungeonLevel::AddText(const wstring& text)
{
	m_systemTexts.push_back(text);
}

void DungeonLevel::ClearText()
{
	m_systemTexts.clear();
}