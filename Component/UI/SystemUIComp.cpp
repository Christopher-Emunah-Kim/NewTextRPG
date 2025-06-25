#include "SystemUIComp.h"
#include "../../Data/PlayerDataTablePerLevel.h"
#include "../../Object/BaseGameObject.h"
#include "../../Screen.h"
#include "../../Util/OutputSystem.h"

SystemUIComp::SystemUIComp(BaseGameObject* owner)
	: BaseComponent(owner, 10), m_playerInfo(DEFAULT_LEVEL)
{
}

void SystemUIComp::Render(Screen* screen)  
{  
    if (screen == nullptr)  
    {  
		return;
    }  

	RenderPlayerInfo(screen);

	RenderSystemText(screen);
}

void SystemUIComp::SetText(const wstring& text)
{
	EnqueueText(text);
}

void SystemUIComp::EnqueueText(const wstring& text)
{
	if (m_textQueue.size() >= MAX_LINES)
	{
		m_textQueue.pop();
	}

	m_textQueue.push(text);
}


void SystemUIComp::ClearTexts()
{
	queue<wstring> emptyQueue;
	m_textQueue.swap(emptyQueue);
}


void SystemUIComp::UpdatePlayerInfo(const FPlayerInfo& playerInfo)
{
	m_playerInfo = playerInfo;
}


void SystemUIComp::RenderPlayerInfo(Screen* screen)
{
	int8 leftMargin = LEFT_MARGIN;

	for (int16 y = 0; y < SCREEN_HEIGHT; ++y)
	{
		screen->Draw(2, y, L"|");
	}

	int16 y = PLAYER_UI_BASE_Y;

	screen->Draw(leftMargin, ++y, L"플레이어  정보");
	++y;
	screen->Draw(leftMargin, ++y, L"--------------------------");
	++y;
	screen->Draw(leftMargin, ++y, L"아이디 : " + m_playerInfo.name);
	++y;
	screen->Draw(leftMargin, ++y, L"레벨 : " + to_wstring(m_playerInfo.playerLevel));
	++y;
	screen->Draw(leftMargin, ++y, L"--------------------------");
	++y;
	screen->Draw(leftMargin, ++y, L"체력 : " + to_wstring(m_playerInfo.health) + L" / " + to_wstring(m_playerInfo.maxHealth));	
	++y;
	screen->Draw(leftMargin, ++y, L"경험치 : " + to_wstring(m_playerInfo.experience.GetCurrentExp()) + L" / " + to_wstring(m_playerInfo.experience.GetMaxExp()));
	++y;
	screen->Draw(leftMargin, ++y, L"보유 금액 : " + to_wstring(m_playerInfo.gold.GetAmount()));
	++y;
	++y;
	screen->Draw(leftMargin, ++y, L"플레이어  스테이터스");
	++y;
	screen->Draw(leftMargin, ++y, L"--------------------------");
	++y;
	screen->Draw(leftMargin, ++y, L"공격력 : " + to_wstring(m_playerInfo.status.GetAttack()));
	++y;
	screen->Draw(leftMargin, ++y, L"방어력 : " + to_wstring(m_playerInfo.status.GetDefense()));
	++y;
	screen->Draw(leftMargin, ++y, L"민첩성 : " + to_wstring(m_playerInfo.status.GetAgility()));
	++y;
	screen->Draw(leftMargin, ++y, L"--------------------------");

	for (int16 y = 0; y < SCREEN_HEIGHT; ++y)
	{
		screen->Draw(PLAYERINFO_PANEL_WIDTH, y, L"|");
	}
}


void SystemUIComp::RenderSystemText(Screen* screen)
{
	vector<wstring> tempTexts;
	queue<wstring> copiedQueue = m_textQueue;

	while (false == copiedQueue.empty())
	{
		tempTexts.push_back(copiedQueue.front());
		copiedQueue.pop();
	}

	int32 outputY = DEFAULT_BASE_Y;
	int32 messageAreaWidth = SCREEN_WIDTH - GAME_PANEL_START_X - 2;
	wstring clearLine(messageAreaWidth, L' ');

	for (int32 y = DEFAULT_BASE_Y; y < DEFAULT_BASE_Y + MAX_LINES; ++y)
	{
		screen->Draw(GAME_PANEL_START_X + 1, y, clearLine);
	}

	for (size_t i = tempTexts.size(); i > 0; --i)
	{
		screen->Draw(GAME_PANEL_START_X + 1, outputY, tempTexts[i - 1]);
		++outputY;
	}
}
