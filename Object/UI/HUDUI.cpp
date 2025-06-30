#include "HUDUI.h"
#include "../../Level/BaseLevel.h"
#include "../../Object/Character/Player.h"
#include "../../Util/OutputSystem.h"
#include "../../Component/Player/PlayerStatusComp.h"
#include "../../Data/PlayerDataTablePerLevel.h"
#include "../../Screen.h"
#include "../../Util/InputSystem.h"


HUDUI::HUDUI(BaseLevel* level)
	: BaseGameObject(level, L"HUDUI"), m_playerInfo(DEFAULT_LEVEL)
{
}


void HUDUI::Init()
{
	SetPosition(0, 0);


	BaseGameObject::Init();

}

void HUDUI::Render(Screen* screen)
{
	if (screen == nullptr)
	{
		return;
	}

	RenderPlayerInfo(screen);

	RenderSystemText(screen);

	BaseGameObject::Render(screen);
}

void HUDUI::UpdatePlayerInfoDialog(const Player& player)
{
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

	const FPlayerInfo& playerInfo = statusComp->GetPlayerInfo();
	UpdatePlayerInfo(playerInfo);
	
}

void HUDUI::RegisterInNewLevel(BaseLevel* newLevel)
{
	if (GetLevel() != newLevel)
	{
		if (GetLevel())
		{
			GetLevel()->DetachObject(this);
		}

		SetLevelArea(newLevel);
		
		if (newLevel)
		{
			newLevel->AddObject(this);
		}
	}
}

void HUDUI::SetSystemText(const wstring& text)
{
	EnqueueText(text);
	
}

void HUDUI::EnqueueText(const wstring& text)
{
	if (m_textQueue.size() >= MAX_LINES)
	{
		m_textQueue.pop();
	}

	m_textQueue.push(text);
}

void HUDUI::ClearSystemText()
{
	queue<wstring> emptyQueue;
	m_textQueue.swap(emptyQueue);
}

void HUDUI::UpdatePlayerInfo(const FPlayerInfo& playerInfo)
{
	m_playerInfo = playerInfo;
}



void HUDUI::RenderPlayerInfo(Screen* screen)
{
	screen->Draw(0, 0, L"┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐");

	for (int16 y = 1; y < SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT; ++y)
	{
		screen->Draw(0, y, L"│");
		screen->Draw(PLAYERINFO_PANEL_WIDTH, y, L"│");
		screen->Draw(SCREEN_WIDTH - 2, y, L"│");
	}

	screen->Draw(LEFT_MARGIN + 5, 1, L"[ WELCOM TO TRPG ]");

	//TODO : 맵이름 UI에 설정하기
	screen->Draw((int32)(SCREEN_WIDTH * 0.55f), 1, L"<< 맵 이름 >>");

	int16 y = PLAYER_UI_BASE_Y;

	screen->Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	screen->Draw(GAME_PANEL_START_X, y, L"────────────────────────────────────────────────────────────────────────────────────────────");
	screen->Draw(LEFT_MARGIN, ++y, L"     [ 플레이어  정보 ]");
	screen->Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"아이디 : " + m_playerInfo.name);
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"레벨 : " + to_wstring(m_playerInfo.characterLevel));
	++y;
	screen->Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"체력 : " + to_wstring(m_playerInfo.health) + L" / " + to_wstring(m_playerInfo.maxHealth));
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"경험치 : " + to_wstring(m_playerInfo.experience.GetCurrentExp()) + L" / " + to_wstring(m_playerInfo.experience.GetMaxExp()));
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"보유 금액 : " + to_wstring(m_playerInfo.gold.GetAmount()));
	++y;
	screen->Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	screen->Draw(LEFT_MARGIN, ++y, L"  [ 플레이어  스테이터스 ]");
	screen->Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"공격력 : " + to_wstring(m_playerInfo.status.GetAttack()));
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"방어력 : " + to_wstring(m_playerInfo.status.GetDefense()));
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"민첩성 : " + to_wstring(m_playerInfo.status.GetAgility()));
	++y;
	screen->Draw(LEFT_MARGIN - 2, ++y, L"───────────────────────────────");
	screen->Draw(LEFT_MARGIN, ++y, L"사용 무기: ");
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"사용 방어구: ");
	++y;
	screen->Draw(LEFT_MARGIN, ++y, L"가방: ");
	++y;

	screen->Draw(0, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT, L"│─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│");
	screen->Draw(0, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, L"│");
	screen->Draw(2, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, L"명령 > ");

	//TODO 입력버퍼 위치조정
	screen->Draw(9, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, InputSystem::GetBuffer());

	screen->Draw(SCREEN_WIDTH - 2, SCREEN_HEIGHT - COMMAND_BLOCK_HEIGHT + 1, L"│");
	screen->Draw(0, SCREEN_HEIGHT - 1, L"└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘");

	//screen->Draw(GAME_PANEL_START_X, DEFAULT_BASE_Y, L"────────────────────────────────────────────────────────────────────────────────────────────");
}

void HUDUI::RenderSystemText(Screen* screen)
{
	vector<wstring> tempTexts;
	queue<wstring> copiedQueue = m_textQueue;

	while (false == copiedQueue.empty())
	{
		tempTexts.push_back(copiedQueue.front());
		copiedQueue.pop();
	}

	int32 outputY = SYSTEM_TEXT_BASE_Y;
	int32 messageAreaWidth = SCREEN_WIDTH - GAME_PANEL_START_X - RIGHT_MARGIN;

	wstring clearLine(messageAreaWidth, L' ');

	for (int32 y = outputY; y < outputY + MAX_LINES; ++y)
	{
		screen->Draw(GAME_PANEL_START_X + 1, y, clearLine);
	}

	for (size_t i = 0; i < tempTexts.size(); ++i)
	{
		screen->Draw(GAME_PANEL_START_X + 1, outputY, tempTexts[i]);
		++outputY;
	}
}