#include "TestLevel.h"
#include "../Object/BaseGameObject.h"
#include "../Object/Player.h"
#include "../Core/GameInstance.h"
#include "../Util/InputSystem.h"
#include "../Object/SystemTextDialog.h"


void TestLevel::Init()
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
		systemTextDialog->SetSystemText("테스트 레벨에 오신 것을 환영합니다.");
	}

	BaseLevel::Init();
}

void TestLevel::Update()
{
	BaseLevel::Update();

}