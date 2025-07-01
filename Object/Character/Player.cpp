#include "Player.h"
#include "../../Screen.h"
#include "../../Core/GameInstance.h"
#include "../../Level/BaseLevel.h"
#include "../../Component/Player/EquipmentComp.h"
#include "../../Component/Player/PlayerStatusComp.h"
#include "../../Component/Player/InventoryComp.h"



Player::Player()
	:BattleCharacter(nullptr, L"Player"), m_playerInfo(DEFAULT_LEVEL)
{
}


void Player::Init()
{
	SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	if (false == HasComponentType<PlayerStatusComp>())
	{
		AddComponent(new PlayerStatusComp(this));
	}

	BattleCharacter::Init();
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

		SetLevelArea(level);

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



