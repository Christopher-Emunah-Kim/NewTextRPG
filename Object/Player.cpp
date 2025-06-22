#include "Player.h"
#include "../Screen.h"
#include "../Component/ControllerComp.h"
#include "../Component/RendererComp.h"
#include "../Level/BaseLevel.h"



void Player::Init()
{
	SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	if (false == HasComponentType<ControllerComp>())
	{
		AddComponent(new ControllerComp(this));
	}
	if (false == HasComponentType<RendererComp>())
	{
		AddComponent(new RendererComp(this, L"@"));
	}

	BaseGameObject::Init();
}

void Player::RegisterNewLevelArea(BaseLevel* level)
{
	if (level != nullptr)
	{
		if (GetLevel() == level)
			return;

		if (GetLevel() != nullptr)
		{
			GetLevel()->DetachObject(this);
		}

		SetLevel(level);

		if (IsComponentsEmpty())
		{
			Init();
		}

		if (level->FindObject(L"Player") == nullptr)
		{
			level->AddObject(this);
		}
	}
}
