#include "PlayerInfoUIComp.h"
#include "../../../NewTextRPG/Screen.h"
#include "../../Data/PlayerDataTablePerLevel.h"
#include "../../Util/OutputSystem.h"

PlayerInfoUIComp::PlayerInfoUIComp(BaseGameObject* owner)
	: BaseComponent(owner, 3), m_playerInfo(DEFAULT_LEVEL)
{
}

void PlayerInfoUIComp::Render(Screen* screen)
{
	if (screen == nullptr)
	{
		return;
	}


	int8 leftMargin = 4;

	for (int16 y = 0; y < SCREEN_HEIGHT; ++y)
	{
		screen->Draw(2, y, L"|");
	}

	int16 y = 2;
	screen->Draw(leftMargin, ++y, L"플레이어  정보");
	screen->Draw(leftMargin, y++, L"--------------------------");

	++y;

	screen->Draw(leftMargin, ++y, L"아이디 : " + m_playerInfo.name);
	screen->Draw(leftMargin, ++y, L"레벨 : " + to_wstring(m_playerInfo.playerLevel));

	++y;

	screen->Draw(leftMargin, ++y, L"체력 : " + to_wstring(m_playerInfo.health) + L" / " + to_wstring(m_playerInfo.maxHealth));
	screen->Draw(leftMargin, ++y, L"경험치 : " + to_wstring(m_playerInfo.experience.GetCurrentExp()) + L" / " + to_wstring(m_playerInfo.experience.GetMaxExp()));
	screen->Draw(leftMargin, ++y, L"보유 금액 : " + to_wstring(m_playerInfo.gold.GetAmount()));

	++y;
	++y;

	screen->Draw(leftMargin, ++y, L"플레이어  스테이터스");
	screen->Draw(leftMargin, ++y, L"--------------------------");

	++y;

	screen->Draw(leftMargin, ++y, L"공격력 : " + to_wstring(m_playerInfo.status.GetAttack()));
	screen->Draw(leftMargin, ++y, L"방어력 : " + to_wstring(m_playerInfo.status.GetDefense()));
	screen->Draw(leftMargin, ++y, L"민첩성 : " + to_wstring(m_playerInfo.status.GetAgility()));

	++y;

	for (int16 y = 0; y < SCREEN_HEIGHT; ++y)
	{
		screen->Draw(PLAYERINFO_PANEL_WIDTH, y, L"|");
	}

}

void PlayerInfoUIComp::UpdatePlayerInfo(const FPlayerInfo& playerInfo)
{
	m_playerInfo = playerInfo;
}

