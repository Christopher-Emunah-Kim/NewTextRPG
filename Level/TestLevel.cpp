#include "TestLevel.h"
#include "../Object/BaseGameObject.h"
#include "../Object/Player.h"
#include "../Core/GameInstance.h"
#include "../Util/InputSystem.h"


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

	BaseLevel::Init();
}

void TestLevel::Update()
{
	BaseLevel::Update();

}