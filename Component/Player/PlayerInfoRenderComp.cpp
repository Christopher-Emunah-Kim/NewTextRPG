#include "PlayerInfoRenderComp.h"
#include "../../../NewTextRPG/Screen.h"
#include "../../Data/PlayerDataTablePerLevel.h"

PlayerInfoRenderComp::PlayerInfoRenderComp(BaseGameObject* owner)
	: BaseComponent(owner, 3),
	m_playerName(L"Player"),
	m_level(1),
	m_health(DEFAULT_CHARACTER_MAX_HEALTH),
	m_maxHealth(DEFAULT_CHARACTER_MAX_HEALTH),
	m_experience(0),
	m_maxExperience(DEFAULT_PLAYER_MAX_EXPERIENCE),
	m_attack(DEFAULT_ATTACK),
	m_defense(DEFAULT_DEFENSE),
	m_agility(DEFAULT_AGILITY),
	m_gold(0)
{
}

void PlayerInfoRenderComp::Render(Screen* screen)
{
	if (screen == nullptr)
		return;

	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		screen->Draw(PLAYERINFO_PANEL_WIDTH, y, L"|");
	}

	int y = 2;
	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"플레이어 정보");
	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"--------------------");

	y++;

	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"아이디 : " + m_playerName);
	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"레벨 : " + to_wstring(m_level));

	y++;

	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"체력 : " + to_wstring(m_health) + L"/" + to_wstring(m_maxHealth));
	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"경험치 : " + to_wstring(m_experience) + L"/" + to_wstring(m_maxExperience));
	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"Gold: " + to_wstring(m_gold));

	y++;

	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"플레이어 스테이터스");
	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"---------------");

	y++;

	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"공격력 : " + to_wstring(m_attack));
	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"방어력 : " + to_wstring(m_defense));
	screen->Draw(PLAYERINFO_PANEL_WIDTH + 2, y++, L"민첩성 : " + to_wstring(m_agility));

	y++; 

}

void PlayerInfoRenderComp::UpdateStatus(const wstring& name, int16 level, int32 health, int32 maxHealth, int32 exp, int32 maxExp, int16 attack, int16 defense, int16 agility, int32 gold)  
{  
    m_playerName = name;  
    m_level = level;  
    m_health = health;  
    m_maxHealth = maxHealth;  
    m_experience = exp;  
    m_maxExperience = maxExp;  
    m_attack = attack;  
    m_defense = defense;  
    m_agility = agility;  
    m_gold = gold;  
}
