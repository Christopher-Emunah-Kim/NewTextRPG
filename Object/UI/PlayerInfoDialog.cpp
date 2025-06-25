#include "PlayerInfoDialog.h"
#include "../../Level/BaseLevel.h"
#include "../../Component/UI/PlayerInfoUIComp.h"
#include "../../Object/Player.h"
#include "../../Util/OutputSystem.h"
#include "../../Component/Player/PlayerStatusComp.h"

PlayerInfoDialog::PlayerInfoDialog(BaseLevel* level)
	: BaseGameObject(level, L"PlayerInfoDialog")
{
}

void PlayerInfoDialog::Init()
{
	SetPosition(0, 0);

	//OutputSystem::PrintInfoMsg(L"PlayerInfoDialog::Init 호출됨");

	if (false == HasComponentType<PlayerInfoUIComp>())
	{
		m_renderComp =  new PlayerInfoUIComp(this);
		AddComponent(m_renderComp);
		//OutputSystem::PrintInfoMsg(L"PlayerInfoRenderComp 생성됨");
	}
	else
	{
		vector<BaseComponent*> comps = GetComponents();
		for (size_t i = 0; i < comps.size(); ++i)
		{
			m_renderComp = dynamic_cast<PlayerInfoUIComp*>(comps[i]);
			if (m_renderComp)
			{
				//OutputSystem::PrintInfoMsg(L"기존 PlayerInfoRenderComp 찾음");
				break;
			}
		}
	}

	BaseGameObject::Init();
}

void PlayerInfoDialog::UpdatePlayerInfoDialog(const Player& player)
{
	//TODO : 음 이걸 굳이 매번 새 객체포인터를 가지고 지정해야하는걸까?
	//TODO : 수정필요
	const PlayerStatusComp* statusComp = nullptr;
    const vector<BaseComponent*>& playerComps = const_cast<Player&>(player).GetComponents();

	for (size_t i = 0; i < playerComps.size(); ++i)
	{
		statusComp = dynamic_cast<PlayerStatusComp*>(playerComps[i]);
		if (statusComp)
		{
			break;
		}
	}

	if (nullptr == statusComp)
	{
		OutputSystem::PrintErrorMsg(L"플레이어에 PlayerStatusComp가 없습니다.");
		return;
	}


	if (m_renderComp)
	{
		const FPlayerInfo& playerInfo = statusComp->GetPlayerInfo();
		m_renderComp->UpdatePlayerInfo(playerInfo);
	}
	else
	{
		OutputSystem::PrintErrorMsg(L"PlayerInfoDialog에 PlayerInfoRenderComp가 존재하지 않습니다.");
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
