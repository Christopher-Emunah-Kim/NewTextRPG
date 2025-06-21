#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/SystemTextDialog.h"


void TitleLevel::Init()
{
	GameInstance* gameInstance = GameInstance::GetInstance();
	Player& player = gameInstance->GetPlayer();

	player.UpdateLevel(this);

	if (false == gameInstance->IsPlayerInitialzed())
	{
		gameInstance->SetPlayerInitialize(true);
	}

	if (FindObject("Player") == nullptr)
	{
		AddObject(&player);
	}

	if (FindObject("SystemTextDialog") == nullptr)
	{
		SystemTextDialog* systemTextDialog = new SystemTextDialog(this);
		AddObject(systemTextDialog);
		systemTextDialog->SetSystemText("타이틀 화면입니다. 이동하려면 WASD를 누르세요");
	}

	BaseLevel::Init();
}

void TitleLevel::Update()
{
	BaseLevel::Update();


}