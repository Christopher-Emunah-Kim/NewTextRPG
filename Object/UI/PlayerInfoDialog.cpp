#include "PlayerInfoDialog.h"
#include "../../Level/BaseLevel.h"
#include "../../Component/Player/PlayerInfoComp.h"

PlayerInfoDialog::PlayerInfoDialog(BaseLevel* level)
	: BaseGameObject(level, L"PlayerInfoDialog")
{
}

void PlayerInfoDialog::Init()
{
	SetPosition(0, 0);

	if (false == HasComponentType<PlayerInfoComp>())
	{
		AddComponent(new PlayerInfoComp(this));
	}

	BaseGameObject::Init();
}

void PlayerInfoDialog::UpdatePlayerInfoDialog(const Player& player)
{
	//TODO : 음 이걸 굳이 매번 새 객체포인터를 가지고 지정해야하는걸까?
	PlayerInfoComp* infoComp = nullptr;
	vector<BaseComponent*> components = GetComponents();

	for (size_t i = 0; i < components.size(); ++i)
	{
		infoComp = dynamic_cast<PlayerInfoComp*>(components[i]);
		if (infoComp)
		{
			infoComp->UpdateStatus(player);
			break;
		}
	}

}

void PlayerInfoDialog::RegisterPlayerInfoDialogInNewLevel(BaseLevel* newLevel)
{
	if (GetLevel() != newLevel)
	{
		if (GetLevel())
		{
			GetLevel()->DetachObject(this);
		}

		SetLevel(newLevel);
		
		if (newLevel)
		{
			newLevel->AddObject(this);
		}
	}
}
