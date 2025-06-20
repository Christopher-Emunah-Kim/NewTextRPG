#include "TitleLevel.h"
#include "../Core/GameInstance.h"


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

	BaseLevel::Init();
}

void TitleLevel::Update()
{
	BaseLevel::Update();


}