#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/UI/HUDUI.h"
#include "../Screen.h"
#include "../Util/InputSystem.h"
#include "../Manager/LevelManager.h"


void TitleLevel::Init()
{
	GameInstance* gameInstance = GameInstance::GetInstance();
	Player& player = gameInstance->GetPlayer();

	player.RegisterNewLevelArea(this);

	if (false == gameInstance->IsPlayerInitialzed())
	{
		gameInstance->SetPlayerInitialize(true);
	}

	m_player = &player;
	m_player->SetPosition(GAME_PANEL_START_X + (SCREEN_WIDTH - GAME_PANEL_START_X) / 2, SCREEN_HEIGHT / 2);


	if (nullptr == gameInstance->GetHUDUI())
	{
		HUDUI* playerHUD = new HUDUI(this);
		playerHUD->Init();
		gameInstance->SetHUDUI(playerHUD);
	}

	gameInstance->UpdatePlayerInfo();
	
	gameInstance->DisplaySystemText(L"타이틀 화면입니다.");
	gameInstance->DisplaySystemText(L"이동하려면 WASD를 누르세요");
	gameInstance->DisplaySystemText(L"==========================");
	gameInstance->DisplaySystemText(L"[메뉴 옵션]");
	gameInstance->DisplaySystemText(L"1. 마을로 들어가기");
	gameInstance->DisplaySystemText(L"2. 던전으로 이동하기");
	gameInstance->DisplaySystemText(L"3. 게임 종료");
	gameInstance->DisplaySystemText(L"==========================");
	gameInstance->DisplaySystemText(L"원하는 옵션의 번호를 입력하세요.");
	gameInstance->DisplaySystemText(L"Enter 키를 눌러 커맨드입력 / 컨트롤 모드를 변경해보세요");

	//InputSystem::StartTextInput();

	BaseLevel::Init();
}

void TitleLevel::Update()
{
	BaseLevel::Update();

	ProcessTitleMenuInput();
}

void TitleLevel::ProcessTitleMenuInput()
{
	if (!InputSystem::IsAcceptingTextInput())
	{
		return;
	}

	wstring cmd = InputSystem::GetCommand();

	if (cmd.empty())
	{
		return;
	}

	GameInstance* gameinstance = GameInstance::GetInstance();
	

	if (cmd == L"1")
	{
		gameinstance->DisplaySystemText(L"게임을 시작합니다...");
		LevelManager::GetInstance()->SetNextLevel(L"VillageLevel"); // TODO 다음 레벨 설정
		BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();
		gameinstance->ChangeLevelAreaSettings(nextLevel);
		InputSystem::StopTextInput();
	}
	else if (cmd == L"2")
	{
		gameinstance->DisplaySystemText(L"던전으로 이동합니다...");
		LevelManager::GetInstance()->SetNextLevel(L"DungeonLevel"); // TODO 다음 레벨 설정
		BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();
		gameinstance->ChangeLevelAreaSettings(nextLevel);
		InputSystem::StopTextInput();
	}
	else if (cmd == L"3")
	{
		gameinstance->DisplaySystemText(L"게임을 종료합니다...");
		InputSystem::StopTextInput();
		exit(0); // 게임 종료
	}
	else
	{
		InputSystem::StopTextInput();
		InputSystem::StartTextInput();
	}
}
