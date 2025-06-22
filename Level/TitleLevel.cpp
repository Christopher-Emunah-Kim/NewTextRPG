#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/SystemTextDialog.h"
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

	if (FindObject(L"SystemTextDialog") == nullptr)
	{
		SystemTextDialog* systemTextDialog = new SystemTextDialog(this);
		if (systemTextDialog != nullptr)
		{
			gameInstance->SetSystemTextDialog(systemTextDialog);
			gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");
		}
	}

	m_player->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	BaseLevel::Init();
}

void TitleLevel::Update()
{
	BaseLevel::Update();


}