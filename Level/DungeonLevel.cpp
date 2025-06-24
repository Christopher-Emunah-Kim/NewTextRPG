#include "DungeonLevel.h"
#include "../Core/GameInstance.h"
#include "../Util/OutputSystem.h"
#include "../Object/BaseGameObject.h"
#include "../Component/Player/PlayerInfoUpdateComp.h"

void DungeonLevel::Init()
{
	GameInstance* gameInstance = GameInstance::GetInstance();

	if (!gameInstance->LoadSerializedDataFromFile(this, L"DataDriven/Dungeon.txt"))
	{
		OutputSystem::PrintErrorMsg(L"DungeonLevel 데이터를 로드하는데 실패했습니다.");

		if (gameInstance->GetPlayer())
		{
			m_player = gameInstance->GetPlayer();
			m_player->RegisterNewLevelArea(this);
			AddObject(m_player);
		}

		BaseGameObject* infoPanel = new BaseGameObject(this, L"InfoPanel", L"InfoPanel");
		infoPanel->SetMessage(L"플레이어 상태 패널");

		PlayerInfoUpdateComp* infoComp = new PlayerInfoUpdateComp(infoPanel);
		infoPanel->AddComponent(infoComp);
		AddObject(infoPanel);
		infoPanel->Init();

		if (m_player)
		{
			gameInstance->InitPlayerInfoPanel(infoPanel, m_player);
		}
	}
	else
	{
		gameInstance->ChangeLevelAreaSettings(this);
	}



	gameInstance->DisplaySystemText(L"던전에 입장했습니다");

	BaseLevel::Init();
}

void DungeonLevel::Update()
{
	BaseLevel::Update();
}