#include "Player.h"
#include "../../Screen.h"
#include "../../Component/ControllerComp.h"
#include "../../Component/UI/MeshUIComp.h"
#include "../../Level/BaseLevel.h"
#include "../../Component/Player/PlayerStatusComp.h"



void Player::Init()
{
	SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	if (false == HasComponentType<ControllerComp>())
	{
		AddComponent(new ControllerComp(this));
	}
	if (false == HasComponentType<MeshUIComp>())
	{
		AddComponent(new MeshUIComp(this, L"@"));
	}
	if (false == HasComponentType<PlayerStatusComp>())
	{
		AddComponent(new PlayerStatusComp(this));
	}

	BaseGameObject::Init();
}

void Player::RegisterNewLevelArea(BaseLevel* level)
{
	if (level != nullptr)
	{
		if (GetLevel() == level)
		{
			return;
		}

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
