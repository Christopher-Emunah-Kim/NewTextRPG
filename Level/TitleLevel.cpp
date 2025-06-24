#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/UI/SystemTextDialog.h"
#include "../Object/BaseGameObject.h"
#include "../Screen.h"
#include "../Component/Player/PlayerStatusComp.h"
#include "../Component/Player/PlayerInfoUpdateComp.h"
#include "../Util/OutputSystem.h"
#include "../Component/SystemTextComp.h"


void TitleLevel::Init()
{
	GameInstance* gameInstance = GameInstance::GetInstance();

	if (!gameInstance->LoadSerializedDataFromFile(this, L"DataDriven/Title.txt"))
	{
		OutputSystem::PrintErrorMsg(L"TitleLevel 데이터를 로드하는데 실패했습니다.");

		if (gameInstance->GetPlayer())
		{
			m_player = gameInstance->GetPlayer();
			m_player->RegisterNewLevelArea(this);
		}
		else
		{
			m_player = new BaseGameObject(this, L"Player", L"Player");

			m_player->SetMessage(L"새로운 플레이어입니다.");

			m_player->SetCustomField(L"level", L"1");
			m_player->SetCustomField(L"health", L"100");
			m_player->SetCustomField(L"maxHealth", L"100");
			m_player->SetCustomField(L"exp", L"0");
			m_player->SetCustomField(L"maxExp", L"100");
			m_player->SetCustomField(L"attack", L"12");
			m_player->SetCustomField(L"defense", L"12");
			m_player->SetCustomField(L"agility", L"12");
			m_player->SetCustomField(L"gold", L"0");

			PlayerStatusComp* statusComp = new PlayerStatusComp(m_player);
			m_player->AddComponent(statusComp);

			gameInstance->SetPlayer(m_player);

			AddObject(m_player);
			m_player->Init();
		}

		BaseGameObject* infoPanel = new BaseGameObject(this, L"InfoPanel", L"InfoPanel");
		infoPanel->SetMessage(L"플레이어 상태 패널");

		PlayerInfoUpdateComp* infoComp = new PlayerInfoUpdateComp(infoPanel);
		infoPanel->AddComponent(infoComp);
		AddObject(infoPanel);
		infoPanel->Init();

		gameInstance->InitPlayerInfoPanel(infoPanel, m_player);
	}
	else
	{
		gameInstance->ChangeLevelAreaSettings(this);
	}
	

	gameInstance->DisplaySystemText(L"당신의 모험이 시작됩니다..");

	gameInstance->DisplaySystemText(L"저는 당신의 가이드 리얼입니다. 준비가 되셨나요?");

	BaseGameObject* systemTextObj = gameInstance->GetSystemTextDialog();
	if (systemTextObj)
	{
		SystemTextComp* textComp = systemTextObj->GetComponentsByType<SystemTextComp>();
		if (textComp)
		{
			textComp->ClearOption();
			textComp->AddOption(L"1. 게임 정보 보기", L"show_game_info");
			textComp->AddOption(L"2. 던전 입장하기", L"enter_dungeon");
			textComp->AddOption(L"3. 게임 종료하기", L"exit_game");

		}
	}

	BaseLevel::Init();

	/*Player& player = gameInstance->GetPlayer();

	player.RegisterNewLevelArea(this);

	if (false == gameInstance->IsPlayerInitialzed())
	{
		gameInstance->SetPlayerInitialize(true);
	}

	m_player = &player;
	m_player->SetPosition(GAME_PANEL_START_X + (SCREEN_WIDTH - GAME_PANEL_START_X) / 2, SCREEN_HEIGHT / 2);

	if (gameInstance->GetPlayerInfoDialog())
	{
		gameInstance->UpdatePlayerInfo();
	}
	else
	{
		PlayerInfoDialog* dialog = new PlayerInfoDialog(this);
		dialog->Init();
		gameInstance->SetPlayerInfoDialog(dialog);
	}

	gameInstance->DisplaySystemText(L"타이틀 화면입니다. 이동하려면 WASD를 누르세요");
*/
}

void TitleLevel::Update()
{
	BaseLevel::Update();


}