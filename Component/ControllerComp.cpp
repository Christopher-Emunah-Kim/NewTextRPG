#include "ControllerComp.h"
#include "../Object/BaseGameObject.h"
#include "../Util/InputSystem.h"
#include "../Util/OutputSystem.h"
#include "../Screen.h"
#include "../Common.h"
#include <winuser.h>

void ControllerComp::Init()
{
	InputAction* moveUpAction = InputSystem::CreateAction("MoveUp");
	InputAction* moveDownAction = InputSystem::CreateAction("MoveDown");
	InputAction* moveLeftAction = InputSystem::CreateAction("MoveLeft");
	InputAction* moveRightAction = InputSystem::CreateAction("MoveRight");

	moveUpAction->BindCallback([this](EInputEvent event) { HandleMovement(event, EMoveDirection::UP); });
	moveDownAction->BindCallback([this](EInputEvent event) { HandleMovement(event, EMoveDirection::DOWN); });
	moveLeftAction->BindCallback([this](EInputEvent event) { HandleMovement(event, EMoveDirection::LEFT); });
	moveRightAction->BindCallback([this](EInputEvent event) { HandleMovement(event, EMoveDirection::RIGHT); });

	InputSystem::BindAction("MoveUp", 'W');
	InputSystem::BindAction("MoveDown", 'S');
	InputSystem::BindAction("MoveLeft", 'A');
	InputSystem::BindAction("MoveRight", 'D');
	
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
		OutputSystem::PrintErrorMsg("잘못된 방향입니다.");
	}
	}


	if (currentX < 0)
	{
		currentX = 0;
	}
	if (currentX >= SCREEN_WIDTH)
	{
		currentX = SCREEN_WIDTH - 1;
	}
	if (currentY < 0)
	{
		currentY = 0;
	}
	if (currentY >= SCREEN_HEIGHT)
	{
		currentY = SCREEN_HEIGHT - 1;
	}

	m_owner->SetPosition(currentX, currentY);
}



