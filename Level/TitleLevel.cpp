#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/UI/HUDUI.h"
#include "../Screen.h"
#include "../Util/InputSystem.h"
#include "../Manager/LevelManager.h"


void TitleLevel::Init()
{
	GameInstance* gameInstance = GameInstance::GetInstance();
	
	if (nullptr == gameInstance->GetHUDUI())
	{
		m_HUDUI = new HUDUI(this);
		m_HUDUI->Init();
		gameInstance->SetHUDUI(m_HUDUI);
	}

	Welcome();

	//Player* player = gameInstance->GetPlayer();

	//player->RegisterNewLevelArea(this);

	//if (false == gameInstance->IsPlayerInitialzed())
	//{
	//	gameInstance->SetPlayerInitialize(true);
	//}

	//m_player = player;
	//m_player->SetPosition(GAME_PANEL_START_X + (SCREEN_WIDTH - GAME_PANEL_START_X) / 2, SCREEN_HEIGHT / 2);


	BaseLevel::Init();
}

void TitleLevel::Render(Screen* screen)
{
	for (size_t line = 0; line < m_systemTexts.size(); ++line)
	{
		m_HUDUI->EnqueueText(m_systemTexts[line]);
		//screen->Draw(0, line, m_systemTexts[line]);
	}
	//screen->Draw(0, 10, L"입력 : " + InputSystem::GetBuffer());

	BaseLevel::Render(screen);
}

void TitleLevel::Release()
{

}


void TitleLevel::Welcome()
{
	AddText(L"==========================");
	AddText(L"TEXT RPG 에 오신 것을 환영합니다.");
	AddText(L"[메뉴 옵션]");
	AddText(L"1. 마을로 들어가기");
	AddText(L"2. 던전으로 이동하기");
	AddText(L"3. 게임 종료");
	AddText(L"==========================");
	AddText(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&TitleLevel::EnterVillage, this)},
			{L"2", bind(&TitleLevel::EnterDungeon, this)},
			{L"3", bind(&TitleLevel::GoToHell, this)}
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

void TitleLevel::EnterVillage()
{
	ClearText();

	AddText(L"마을로 돌아가기는 개뿔 다시 처음부터입니다.");

	InputSystem::Clear();
	Welcome();
}

void TitleLevel::EnterDungeon()
{
	ClearText();

	AddText(L"던전으로 이동하기는 개뿔 다시 처음부터입니다.");

	InputSystem::Clear();
	Welcome();
}

void TitleLevel::GoToHell()
{
	ClearText();

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



//void TitleLevel::ProcessTitleMenuInput()
//{
//	if (!InputSystem::IsAcceptingTextInput())
//	{
//		return;
//	}
//
//	wstring cmd = InputSystem::GetCommand();
//
//	if (cmd.empty())
//	{
//		return;
//	}
//
//	GameInstance* gameinstance = GameInstance::GetInstance();
//	
//
//	if (cmd == L"1")
//	{
//		gameinstance->DisplaySystemText(L"게임을 시작합니다...");
//		LevelManager::GetInstance()->SetNextLevel(L"VillageLevel"); // TODO 다음 레벨 설정
//		BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();
//		gameinstance->ChangeLevelAreaSettings(nextLevel);
//		InputSystem::StopTextInput();
//	}
//	else if (cmd == L"2")
//	{
//		gameinstance->DisplaySystemText(L"던전으로 이동합니다...");
//		LevelManager::GetInstance()->SetNextLevel(L"DungeonLevel"); // TODO 다음 레벨 설정
//		BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();
//		gameinstance->ChangeLevelAreaSettings(nextLevel);
//		InputSystem::StopTextInput();
//	}
//	else if (cmd == L"3")
//	{
//		gameinstance->DisplaySystemText(L"게임을 종료합니다...");
//		InputSystem::StopTextInput();
//		exit(0); // 게임 종료
//	}
//	else
//	{
//		InputSystem::StopTextInput();
//		InputSystem::StartTextInput();
//	}
//}