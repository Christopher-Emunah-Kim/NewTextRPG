#include "HUDUI.h"
#include "../../Level/BaseLevel.h"
#include "../../Object/Player.h"
#include "../../Util/OutputSystem.h"
#include "../../Component/UI/SystemUIComp.h"
#include "../../Component/Player/PlayerStatusComp.h"

HUDUI::HUDUI(BaseLevel* level)
	: BaseGameObject(level, L"HUDUI")
{
}

void HUDUI::Init()
{
	SetPosition(0, 0);

	if (false == HasComponentType<SystemUIComp>())
	{
		m_UIRenderComp =  new SystemUIComp(this);
		AddComponent(m_UIRenderComp);
	}
	else
	{
		vector<BaseComponent*> comps = GetComponents();
		for (size_t i = 0; i < comps.size(); ++i)
		{
			m_UIRenderComp = dynamic_cast<SystemUIComp*>(comps[i]);
			if (m_UIRenderComp)
			{
				break;
			}
		}
	}

	BaseGameObject::Init();

}

void HUDUI::UpdatePlayerInfoDialog(const Player& player)
{
	//TODO : 음 이걸 굳이 매번 새 객체포인터를 가지고 지정해야하는걸까?
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


	if (m_UIRenderComp)
	{
		const FPlayerInfo& playerInfo = statusComp->GetPlayerInfo();
		m_UIRenderComp->UpdatePlayerInfo(playerInfo);
	}
	else
	{
		OutputSystem::PrintErrorMsg(L"PlayerInfoDialog에 PlayerInfoRenderComp가 존재하지 않습니다.");
	}
	

}

void HUDUI::RegisterInNewLevel(BaseLevel* newLevel)
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

void HUDUI::SetSystemText(const wstring& text)
{
	if (m_UIRenderComp)
	{
		m_UIRenderComp->SetText(text);
	}
	else
	{
		OutputSystem::PrintErrorMsg(L"HUDUI에 SystemUIComp가 존재하지 않습니다.");
	}
}

void HUDUI::ClearSystemText()
{
	if (m_UIRenderComp)
	{
		m_UIRenderComp->ClearTexts();
	}
	else
	{
		OutputSystem::PrintErrorMsg(L"HUDUI에 SystemUIComp가 존재하지 않습니다.");
	}
}