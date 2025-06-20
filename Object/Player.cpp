#include "Player.h"
#include "../Screen.h"
#include "../Component/ControllerComp.h"
#include "../Component/RendererComp.h"
#include "../Level/BaseLevel.h"



void Player::Init()
{
	SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	if (IsComponentsEmpty())
	{
		AddComponent(new ControllerComp(this));
		AddComponent(new RendererComp(this, "@"));
	}

	BaseGameObject::Init();
}

void Player::UpdateLevel(BaseLevel* level)
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

		if (level->FindObject("Player") == nullptr)
		{
			level->AddObject(this);
		}
	}
}
