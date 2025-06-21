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

	player.RegisterNewLevel(this);

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
		GameInstance::GetInstance()->SetSystemTextDialog(systemTextDialog);
	}
	/*BaseGameObject* portalObject = new BaseGameObject(this, "Portal");
	portalObject->SetPosition(LEVEL_TRANSITION_POSITION_X, LEVEL_TRANSITION_POSITION_Y);
	portalObject->AddComponent(new RendererComp(portalObject, "O"));
	AddObject(portalObject);*/

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
	BaseGameObject* player = FindObject("Player");
	if (player == nullptr)
		return;

	int32 playerX = player->GetX();
	int32 playerY = player->GetY();

	bool bInTransitionArea =
		(playerX >= LEVEL_TRANSITION_POSITION_X - TRANSITION_AREA_RADIUS && playerX <= LEVEL_TRANSITION_POSITION_X + TRANSITION_AREA_RADIUS) &&
		(playerY >= LEVEL_TRANSITION_POSITION_Y - TRANSITION_AREA_RADIUS && playerY <= LEVEL_TRANSITION_POSITION_Y + TRANSITION_AREA_RADIUS);

	if (bInTransitionArea && false == m_playerInTransitionArea)
	{
		GameInstance::GetInstance()->DisplaySystemText("포털 지역에 진입했습니다. 스페이스바를 누르면 타이틀 지역으로 진입합니다.");
		m_playerInTransitionArea = true;
		m_diplayedTransitionMessage = true;
	}
	else if (false == bInTransitionArea && m_playerInTransitionArea)
	{
		GameInstance::GetInstance()->DisplaySystemText("포털 지역을 벗어났습니다.");
		m_playerInTransitionArea = false;
		m_diplayedTransitionMessage = false;
	}

	if (m_playerInTransitionArea && InputSystem::IsKeyPressed(EKeyCode::SPACE))
	{
		LevelManager::GetInstance()->SetNextLevel("Title");
	}

}