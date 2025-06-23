#include "TestLevel.h"
#include "../Object/BaseGameObject.h"
#include "../Object/Player.h"
#include "../Core/GameInstance.h"
#include "../Util/InputSystem.h"
#include "../Object/SystemTextDialog.h"
#include <WinUser.h>
#include "../Manager/LevelManager.h"




void TestLevel::Init()
{
	GameInstance* gameInstance = GameInstance::GetInstance();
	Player& player = gameInstance->GetPlayer();

	player.RegisterNewLevelArea(this);

	if (false == gameInstance->IsPlayerInitialzed())
	{
		gameInstance->SetPlayerInitialize(true);
	}

	m_player = &player;

	gameInstance->DisplaySystemText(L"테스트 레벨에 진입하였습니다.");

	m_playerInTransitionArea = false;
	m_diplayedTransitionMessage = false;

	BaseLevel::Init();
}

void TestLevel::Update()
{
	BaseLevel::Update();

	CheckPlayerInTransitionArea();
}


void TestLevel::CheckPlayerInTransitionArea()
{
	if (m_player == nullptr)
		return;

	int32 playerX = m_player->GetX();
	int32 playerY = m_player->GetY();

	bool bInTransitionArea =
		(playerX >= LEVEL_TRANSITION_POSITION_X - TRANSITION_AREA_RADIUS && playerX <= LEVEL_TRANSITION_POSITION_X + TRANSITION_AREA_RADIUS) &&
		(playerY >= LEVEL_TRANSITION_POSITION_Y - TRANSITION_AREA_RADIUS && playerY <= LEVEL_TRANSITION_POSITION_Y + TRANSITION_AREA_RADIUS);


	if (bInTransitionArea && false == m_playerInTransitionArea)
	{
		GameInstance::GetInstance()->DisplaySystemText(L"포털 지역에 진입했습니다. 스페이스바를 누르면 타이틀 지역으로 진입합니다.");
		m_playerInTransitionArea = true;
		m_diplayedTransitionMessage = true;
	}
	else if (false == bInTransitionArea && m_playerInTransitionArea)
	{
		GameInstance::GetInstance()->DisplaySystemText(L"포털 지역을 벗어났습니다.");
		m_playerInTransitionArea = false;
		m_diplayedTransitionMessage = false;
	}

	if (m_playerInTransitionArea && InputSystem::IsKeyPressed(EKeyCode::SPACE))
	{
		LevelManager::GetInstance()->SetNextLevel(L"Title");
	}

}