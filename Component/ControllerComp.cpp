#include "ControllerComp.h"
#include "../Object/BaseGameObject.h"
#include "../Util/InputSystem.h"
#include "../Screen.h"


void ControllerComp::Update()
{
	LONG currentX = m_owner->GetX();
	LONG currentY = m_owner->GetY();

	ApplyInputToPosition(currentY, currentX);

	m_owner->SetPosition(currentX, currentY);
}


void ControllerComp::ApplyInputToPosition(LONG& currentY, LONG& currentX)
{
	if (InputSystem::IsKeyPressed('W'))
	{
		currentY--;
	}
	if (InputSystem::IsKeyPressed('S'))
	{
		currentY++;
	}
	if (InputSystem::IsKeyPressed('A'))
	{
		currentX--;
	}
	if (InputSystem::IsKeyPressed('D'))
	{
		currentX++;
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
}
