#include "HUD.h"
#include "Common.h"
#include "Screen.h"
#include "Util/InputSystem.h"
#include "Util/OutputSystem.h"


void HUD::Render(Screen& screen) const
{
	RenderPlayerInfo(screen);

	RenderSystemText(screen);

	RenderInputBuffer(screen);
}

void HUD::UpdateLevelName(const wstring& levelName)
{
	m_hudData.levelAreaName = levelName;
}

void HUD::UpdatePlayerName(const wstring& playerName)
{
	m_hudData.playerName = playerName;
}

void HUD::UpdatePlayerLevel(int16 level)
{
	m_hudData.playerLevel = level;
}

void HUD::UpdatePlayerHealth(int32 health, int32 maxHealth)
{
	m_hudData.currentHealth = health;
	m_hudData.maxHealth = maxHealth;
}

void HUD::UpdatePlayerStatus(const Status& status)
{
	m_hudData.status = status;
}

void HUD::UpdatePlayerExperience(const Experience& experience)
{
	m_hudData.experience = experience;
}

void HUD::UpdatePlayerGold(const Gold& gold)
{
	m_hudData.gold = gold;
}

void HUD::UpdateEquippedItem(const wstring& name, EItemType type)
{
	if (type == EItemType::Weapon)
	{
		m_hudData.weaponName = name;
	}
	else if (type == EItemType::Armor)
	{
		m_hudData.armorName = name;
	}
}

void HUD::UpdateInvetoryItems(const wstring& name)
{
	if (!m_hudData.inventoryItems.empty() && m_hudData.inventoryItems[0] == L"없음")
	{
		m_hudData.inventoryItems.clear();
	}

	m_hudData.inventoryItems.push_back(name);
}


void HUD::EnqueueText(const wstring& text)
{
	if (m_systemTextQueue.size() >= MAX_LINES)
	{
		m_systemTextQueue.pop_front();
	}

	m_systemTextQueue.push_back(text);
}

void HUD::ClearText()
{
	m_systemTextQueue.clear();
}


void HUD::RenderPlayerInfo(Screen& screen) const
{
	screen.Draw(0, 0, L"┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐");

	for (int16 y = 1; y < SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT; ++y)
	{
		screen.Draw(0, y, L"│");
		screen.Draw(PLAYERINFO_PANEL_WIDTH, y, L"│");
		screen.Draw(SCREEN_WIDTH - 2, y, L"│");
	}

	screen.Draw(LEFT_MARGIN + 5, 1, L"[ WELCOM TO TRPG ]");
	screen.Draw((int32)(SCREEN_WIDTH * 0.55f), 1, L"<< "+ m_hudData.levelAreaName + L" >>");
	screen.Draw(LEFT_MARGIN - 2, PLAYER_UI_BASE_Y + 1, L"───────────────────────────────");
	screen.Draw(GAME_PANEL_START_X, PLAYER_UI_BASE_Y + 1, L"────────────────────────────────────────────────────────────────────────────────────────────");
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 3, L"     [ 플레이어  정보 ]");
	screen.Draw(LEFT_MARGIN - 2, PLAYER_UI_BASE_Y + 4, L"───────────────────────────────");
	PLAYER_UI_BASE_Y + 5;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 6, L"아이디 : " + m_hudData.playerName);
	PLAYER_UI_BASE_Y + 7;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 8, L"레벨 : " + to_wstring(m_hudData.playerLevel));
	PLAYER_UI_BASE_Y + 9;
	screen.Draw(LEFT_MARGIN - 2, PLAYER_UI_BASE_Y + 10, L"───────────────────────────────");
	PLAYER_UI_BASE_Y + 11;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 12, L"체력 : " + to_wstring(m_hudData.currentHealth) + L" / " + to_wstring(m_hudData.maxHealth));
	PLAYER_UI_BASE_Y + 13;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 14, L"경험치 : " + to_wstring(m_hudData.experience.GetCurrentExp()) + L" / " + to_wstring(m_hudData.experience.GetMaxExp()));
	PLAYER_UI_BASE_Y + 15;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 16, L"보유 금액 : " + to_wstring(m_hudData.gold.GetAmount()));
	PLAYER_UI_BASE_Y + 17;
	screen.Draw(LEFT_MARGIN - 2, PLAYER_UI_BASE_Y + 18, L"───────────────────────────────");
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 19, L"  [ 플레이어  스테이터스 ]");
	screen.Draw(LEFT_MARGIN - 2, PLAYER_UI_BASE_Y + 20, L"───────────────────────────────");
	PLAYER_UI_BASE_Y + 21;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 22, L"공격력 : " + to_wstring(m_hudData.status.GetAttack()));
	PLAYER_UI_BASE_Y + 23;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 24, L"방어력 : " + to_wstring(m_hudData.status.GetDefense()));
	PLAYER_UI_BASE_Y + 25;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 26, L"민첩성 : " + to_wstring(m_hudData.status.GetAgility()));
	PLAYER_UI_BASE_Y + 27;
	screen.Draw(LEFT_MARGIN - 2, PLAYER_UI_BASE_Y + 28, L"───────────────────────────────");
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 29, L"사용 무기: " + m_hudData.weaponName);
	PLAYER_UI_BASE_Y + 30;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 31, L"사용 방어구: " + m_hudData.armorName);
	PLAYER_UI_BASE_Y + 32;
	screen.Draw(LEFT_MARGIN, PLAYER_UI_BASE_Y + 33, L"가방: " );

	if (m_hudData.inventoryItems.empty())
	{
		screen.Draw(LEFT_MARGIN + 6, PLAYER_UI_BASE_Y + 33, L"없음");
	}
	else
	{
		screen.Draw(LEFT_MARGIN + 6, PLAYER_UI_BASE_Y + 33, L"[" + m_hudData.inventoryItems[0] + L"]");

		for (size_t i = 1; i < m_hudData.inventoryItems.size(); ++i)
		{
			screen.Draw(LEFT_MARGIN + 6, PLAYER_UI_BASE_Y + 33 + (int32)i,
				L"[" + m_hudData.inventoryItems[i] + L"]");
		}
	}
	
	screen.Draw(0, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT, L"│─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│");
	screen.Draw(0, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, L"│");

	
	
	screen.Draw(SCREEN_WIDTH - 2, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, L"│");
	screen.Draw(0, SCREEN_HEIGHT - 1, L"└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘");

	
}

void HUD::RenderSystemText(Screen& screen) const
{
	int32 messageAreaWidth = SCREEN_WIDTH - GAME_PANEL_START_X - RIGHT_MARGIN;
	wstring clearLine(messageAreaWidth, L' ');

	for (int32 y = SYSTEM_TEXT_BASE_Y + 1; y < SYSTEM_TEXT_BASE_Y + MAX_LINES; ++y)
	{
		screen.Draw(GAME_PANEL_START_X + 1, y, clearLine);
	}

	int32 outputY = SYSTEM_TEXT_BASE_Y + 1;
	for (const auto& text : m_systemTextQueue)
	{
		screen.Draw(GAME_PANEL_START_X + 1, outputY, text);
		++outputY;
	}
}

void HUD::RenderInputBuffer(Screen& screen) const
{
	screen.Draw(2, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, L"명령 > ");
	screen.Draw(9, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, InputSystem::GetBuffer());
}