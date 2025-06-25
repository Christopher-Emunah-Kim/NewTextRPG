#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/UI/HUDUI.h"
#include "../Screen.h"


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
	
	gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");
	gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");
	gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");
	gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");
	gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");
	gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");
	gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");


	BaseLevel::Init();
}

void TitleLevel::Update()
{
	BaseLevel::Update();


}