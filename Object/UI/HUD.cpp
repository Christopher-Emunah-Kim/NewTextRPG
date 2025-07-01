#include "HUD.h"
#include "../Common.h"
#include "../../Screen.h"
#include "../../Util/InputSystem.h"
#include "../../Util/OutputSystem.h"



//HUD::HUD(BaseLevel* level)
//	: BaseGameObject(level, L"HUDUI"), m_playerInfo(DEFAULT_LEVEL)
//{
//}


//void HUD::Init()
//{
//	SetPosition(0, 0);
//
//
//	BaseGameObject::Init();
//
//}

void HUD::Render(Screen& screen) const
{

	RenderPlayerInfo(screen);

	RenderSystemText(screen);

	RenderInputBuffer(screen);
}

//void HUD::UpdatePlayerInfoDialog(const Player& player)
//{
//	const PlayerStatusComp* statusComp = nullptr;
//    const vector<BaseComponent*>& playerComps = const_cast<Player&>(player).GetComponents();
//
//	for (size_t i = 0; i < playerComps.size(); ++i)
//	{
//		statusComp = dynamic_cast<PlayerStatusComp*>(playerComps[i]);
//		if (statusComp)
//		{
//			break;
//		}
//	}
//
//	if (nullptr == statusComp)
//	{
//		OutputSystem::PrintErrorMsg(L"플레이어에 PlayerStatusComp가 없습니다.");
//		return;
//	}
//
//	const FPlayerInfo& playerInfo = statusComp->GetPlayerInfo();
//	UpdatePlayerInfo(playerInfo);
//	
//}
//
//void HUD::RegisterInNewLevel(BaseLevel* newLevel)
//{
//	if (GetLevel() != newLevel)
//	{
//		if (GetLevel())
//		{
//			GetLevel()->DetachObject(this);
//		}
//
//		SetLevelArea(newLevel);
//		
//		if (newLevel)
//		{
//			newLevel->AddObject(this);
//		}
//	}
//}
//
//void HUD::SetSystemText(const wstring& text)
//{
//	EnqueueText(text);
//	
//}

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

//void HUD::UpdatePlayerInfo(const FPlayerInfo& playerInfo)
//{
//	m_playerInfo = playerInfo;
//}



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

	//TODO : 맵이름 UI에 설정하기
	screen.Draw((int32)(SCREEN_WIDTH * 0.55f), 1, L"<< 맵 이름 >>");

	int16 y = PLAYER_UI_BASE_Y;

	screen.Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	screen.Draw(GAME_PANEL_START_X, y, L"────────────────────────────────────────────────────────────────────────────────────────────");
	screen.Draw(LEFT_MARGIN, ++y, L"     [ 플레이어  정보 ]");
	screen.Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"아이디 : " + m_hudData.playerName);
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"레벨 : " + to_wstring(m_hudData.playerLevel));
	++y;
	screen.Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"체력 : " + to_wstring(m_hudData.currentHealth) + L" / " + to_wstring(m_hudData.maxHealth));
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"경험치 : " + to_wstring(m_hudData.experience.GetCurrentExp()) + L" / " + to_wstring(m_hudData.experience.GetMaxExp()));
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"보유 금액 : " + to_wstring(m_hudData.gold.GetAmount()));
	++y;
	screen.Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	screen.Draw(LEFT_MARGIN, ++y, L"  [ 플레이어  스테이터스 ]");
	screen.Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"공격력 : " + to_wstring(m_hudData.status.GetAttack()));
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"방어력 : " + to_wstring(m_hudData.status.GetDefense()));
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"민첩성 : " + to_wstring(m_hudData.status.GetAgility()));
	++y;
	screen.Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	screen.Draw(LEFT_MARGIN, ++y, L"사용 무기: ");
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"사용 방어구: ");
	++y;
	screen.Draw(LEFT_MARGIN, ++y, L"가방: ");
	++y;

	screen.Draw(0, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT, L"│─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│");
	screen.Draw(0, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, L"│");

	
	
	screen.Draw(SCREEN_WIDTH - 2, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, L"│");
	screen.Draw(0, SCREEN_HEIGHT - 1, L"└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘");

	//screen->Draw(GAME_PANEL_START_X, DEFAULT_BASE_Y, L"────────────────────────────────────────────────────────────────────────────────────────────");
}

void HUD::RenderSystemText(Screen& screen) const
{
	/*constexpr size_t textPositionY = DEFAULT_BASE_Y - MAX_LINES;
	for (size_t index = 0; index < m_systemTextQueue.size(); ++index)
	{
		if (textPositionY + index >= static_cast<size_t>(INT32_MAX))
		{
			OutputSystem::PrintErrorMsg(L"텍스트 위치가 INT32 범위를 초과했습니다.");
			break;
		}

		screen.Draw(GAME_PANEL_START_X + 1, static_cast<int32>(textPositionY + index), m_systemTextQueue[index]);
	}*/

	vector<wstring> tempTexts;
	deque<wstring> copiedQueue = m_systemTextQueue;

	while (false == copiedQueue.empty())
	{
		tempTexts.push_back(copiedQueue.front());
		copiedQueue.pop_front();
	}

	int32 outputY = SYSTEM_TEXT_BASE_Y;
	int32 messageAreaWidth = SCREEN_WIDTH - GAME_PANEL_START_X - RIGHT_MARGIN;

	wstring clearLine(messageAreaWidth, L' ');

	for (int32 y = outputY; y < outputY + MAX_LINES; ++y)
	{
		screen.Draw(GAME_PANEL_START_X + 1, y, clearLine);
	}

	for (size_t i = 0; i < tempTexts.size(); ++i)
	{
		screen.Draw(GAME_PANEL_START_X + 1, outputY, tempTexts[i]);
		++outputY;
	}
}

void HUD::RenderInputBuffer(Screen& screen) const
{
	//TODO 입력버퍼 위치조정
	/*screen.Draw(LEFT_MARGIN, COMMAND_BLOCK_HEIGHT, format(L"입력 > {}", InputSystem::GetBuffer()));*/
	screen.Draw(2, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, L"명령 > ");
	screen.Draw(9, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, InputSystem::GetBuffer());
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
