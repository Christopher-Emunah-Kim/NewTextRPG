#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/UI/HUDUI.h"
#include "../Screen.h"
#include "../Util/InputSystem.h"
#include "../Manager/LevelManager.h"
#include "../Component/Player/PlayerStatusComp.h"


TitleLevel::TitleLevel(const wstring& tag)
	:BaseLevel(tag), m_HUDUI(new HUDUI(this))
{
}

void TitleLevel::Init()
{
	SetTitleLevel();

	ProcessTitleMenu();

	BaseLevel::Init();
}

void TitleLevel::Render(Screen* screen)
{
	m_HUDUI->ClearSystemText();

	for (size_t line = 0; line < m_systemTexts.size(); ++line)
	{
		m_HUDUI->EnqueueText(m_systemTexts[line]);
	}

	BaseLevel::Render(screen);
}

void TitleLevel::Release()
{
	delete m_HUDUI;
	m_HUDUI = nullptr;
	GameInstance::GetInstance()->SetHUDUI(nullptr);
}

void TitleLevel::SetTitleLevel()
{
	GameInstance* gameInstance = GameInstance::GetInstance();

	if (nullptr == gameInstance->GetHUDUI())
	{
		//m_HUDUI = new HUDUI(this);
		m_HUDUI->Init();
		gameInstance->SetHUDUI(m_HUDUI);
	}

	Player& player = GameInstance::GetInstance()->GetPlayer();
	PlayerStatusComp* statusComp = player.GetComponentsByType<PlayerStatusComp>();
	if (statusComp)
	{
		statusComp->LoadStatusByLevel();
		const FPlayerInfo& info = player.GetPlayerInfo();
		m_HUDUI->UpdatePlayerInfo(info);
	}
}

void TitleLevel::ProcessTitleMenu()
{
	ClearText();

	AddText(L"============================================");
	AddText(L"당신의 모험을 시작합니다.");
	AddText(L"");
	AddText(L"[메뉴 옵션]");
	AddText(L"");
	AddText(L"1. 마을로 들어가기");
	AddText(L"2. 던전으로 이동하기");
	AddText(L"3. 게임 종료");
	AddText(L"");
	AddText(L"============================================");
	AddText(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&TitleLevel::OnEnterVillage, this)},
			{L"2", bind(&TitleLevel::OnEnterDungeon, this)},
			{L"3", bind(&TitleLevel::OnQuitGame, this)}
		}
	);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			ClearText();
			AddText(L"잘못된 입력입니다. 다시 시도하세요.");
			ProcessTitleMenu();
		}
	);
}


void TitleLevel::OnEnterVillage()
{
	AddText(L"마을로 입장합니다...");

	LevelManager::GetInstance()->SetNextLevel(L"Village"); 
	BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();

	InputSystem::Clear();
}

void TitleLevel::OnEnterDungeon()
{
	AddText(L"끝없는 모험이 당신을 반깁니다...");

	LevelManager::GetInstance()->SetNextLevel(L"Dungeon");
	BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();

	InputSystem::Clear();
}

void TitleLevel::OnQuitGame()
{
	AddText(L"무한 지옥에 오신 것을 환영합니다.");
	AddText(L"ㅎㅎ 장난이에요");

	exit(0); // 게임 종료
}


void TitleLevel::AddText(const wstring& text)
{
	m_systemTexts.push_back(text);
}

void TitleLevel::ClearText()
{
	m_systemTexts.clear();
}

