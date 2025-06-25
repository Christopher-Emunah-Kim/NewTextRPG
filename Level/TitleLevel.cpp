#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/UI/SystemTextDialog.h"
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


	if (nullptr == gameInstance->GetPlayerInfoDialog())
	{
		PlayerInfoDialog* dialog = new PlayerInfoDialog(this);
		dialog->Init();
		gameInstance->SetPlayerInfoDialog(dialog);
	}

	gameInstance->UpdatePlayerInfo();

	if (nullptr == gameInstance->GetSystemTextDialog())
	{
		SystemTextDialog* systemDialog = new SystemTextDialog(this);
		systemDialog->Init();
		gameInstance->SetSystemTextDialog(systemDialog);
	}
	
	gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");

	BaseLevel::Init();
}

void TitleLevel::Update()
{
	BaseLevel::Update();


}