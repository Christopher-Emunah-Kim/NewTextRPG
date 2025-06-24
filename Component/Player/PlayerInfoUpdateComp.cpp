#include "PlayerInfoUpdateComp.h"
#include "../../Object/BaseGameObject.h"
#include "PlayerInfoRenderComp.h"
#include "PlayerStatusComp.h"
#include "../../Util/OutputSystem.h"


PlayerInfoUpdateComp::PlayerInfoUpdateComp(BaseGameObject* owner)
	:BaseComponent(owner, 3)
{
}

void PlayerInfoUpdateComp::Init()  
{  
    m_renderComp = GetOwner()->GetComponentsByType<PlayerInfoRenderComp>();  
    if (nullptr == m_renderComp)  
    {  
        m_renderComp = new PlayerInfoRenderComp(GetOwner());  
		GetOwner()->AddComponent(m_renderComp);
    }  
}

void PlayerInfoUpdateComp::Update()
{
	if (m_player != nullptr)
	{
		UpdatePlayerInfo();
	}
}

void PlayerInfoUpdateComp::UpdatePlayerInfo()
{
	if (nullptr == m_renderComp || nullptr == m_player)
	{
		return;
	}

	PlayerStatusComp* statusComp = m_player->GetComponentsByType<PlayerStatusComp>();
	if (nullptr == statusComp)
	{
		OutputSystem::PrintErrorMsg(L"플레이어에 PlayerStausComp가 없습니다.");
		return;
	}

	const Status& status = statusComp->GetStatus();
	m_renderComp->UpdateStatus(
		statusComp->GetPlayerName(),
		statusComp->GetPlayerLevel(),
		statusComp->GetPlayerHealth(),
		statusComp->GetPlayerMaxHealth(),
		statusComp->GetPlayerExperience(),
		statusComp->GetPlayerMaxExperience(),
		status.GetAttack(),
		status.GetDefense(),
		status.GetAgility(),
		statusComp->GetPlayerGold()
	);

}

void PlayerInfoUpdateComp::SetTargetPlayer(BaseGameObject* player)
{
	m_player = player;
}
