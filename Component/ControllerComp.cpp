#include "ControllerComp.h"
#include "../Object/BaseGameObject.h"
#include "../Util/InputSystem.h"
#include "../Util/OutputSystem.h"
#include "../Screen.h"
#include "../Common.h"
#include <winuser.h>
#include "UI/SystemUIComp.h"

void ControllerComp::Init()
{
	InputAction* moveUpAction = InputSystem::CreateAction(L"MoveUp");
	InputAction* moveDownAction = InputSystem::CreateAction(L"MoveDown");
	InputAction* moveLeftAction = InputSystem::CreateAction(L"MoveLeft");
	InputAction* moveRightAction = InputSystem::CreateAction(L"MoveRight");

	moveUpAction->BindCallback([this](EInputEvent event) { HandleMovement(event, EMoveDirection::UP); });
	moveDownAction->BindCallback([this](EInputEvent event) { HandleMovement(event, EMoveDirection::DOWN); });
	moveLeftAction->BindCallback([this](EInputEvent event) { HandleMovement(event, EMoveDirection::LEFT); });
	moveRightAction->BindCallback([this](EInputEvent event) { HandleMovement(event, EMoveDirection::RIGHT); });

    InputSystem::BindAction(L"MoveUp", static_cast<uint8>(EKeyCode::W));
	InputSystem::BindAction(L"MoveDown", static_cast<uint8>(EKeyCode::S));
	InputSystem::BindAction(L"MoveLeft", static_cast<uint8>(EKeyCode::A));
	InputSystem::BindAction(L"MoveRight", static_cast<uint8>(EKeyCode::D));
	
}

void ControllerComp::Update()
{
	LONG currentX = m_owner->GetX();
	LONG currentY = m_owner->GetY();

	m_owner->SetPosition(currentX, currentY);
}

void ControllerComp::HandleMovement(EInputEvent inputEvent, EMoveDirection direction)
{
	if (inputEvent != EInputEvent::PRESSED && inputEvent != EInputEvent::HOLD)
	{
		return;
	}

	LONG currentX = m_owner->GetX();
	LONG currentY = m_owner->GetY();

	switch (direction)
	{
	case EMoveDirection::UP:
	{
		currentY --;
		break;
	}
	case EMoveDirection::DOWN:
	{
		currentY ++;
		break;
	}
	case EMoveDirection::LEFT:
	{
		currentX --;
		break;
	}
	case EMoveDirection::RIGHT:
	{
		currentX ++;
		break;
	}

	default:
	{
		OutputSystem::PrintErrorMsg(L"잘못된 방향입니다.");
	}
	}


	if (currentX < GAME_PANEL_START_X)
	{
		currentX = GAME_PANEL_START_X;
	}
	if (currentX >= SCREEN_WIDTH)
	{
		currentX = SCREEN_WIDTH - 1;
	}
	if (currentY < 0)
	{
		currentY = 0;
	}
	if (currentY >= DEFAULT_BASE_Y)
	{
		currentY = DEFAULT_BASE_Y - 1;
	}

	m_owner->SetPosition(currentX, currentY);
}



