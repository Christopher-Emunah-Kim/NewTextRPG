#pragma once
#include "../BaseGameObject.h"
#include "../../Util/Type/CharacterInfo.h"
#include <queue>

constexpr __int32 MAX_LINES = 35;
constexpr __int32 DEFAULT_BASE_Y = SCREEN_HEIGHT - MAX_LINES - 4;
constexpr __int8 LEFT_MARGIN = 3;
constexpr __int8 RIGHT_MARGIN = 4;
constexpr __int8 COMMAND_BLOCK_HEIGHT = 3;
constexpr __int16 PLAYER_UI_BASE_Y = 1;
constexpr __int16 SYSTEM_TEXT_BASE_Y = 3;

class Player;
class BaseLevel;
class SystemUIComp;

struct FHudData final
{
	// level area data
	wstring levelAreaName = L"TITLE";

	// player data
	wstring playerName = L"발할라 전사";
	int16 playerLevel = 1;
	int32 currentHealth = 100;
	int32 maxHealth = 100;
	Status status = Status(1,1,1);
	Experience experience;
	Gold gold;
};

class HUD final
{
public:
	HUD() = default;
	virtual ~HUD() = default;

private:
	deque<wstring> m_systemTextQueue;
	FHudData m_hudData;

private:
	void RenderPlayerInfo(Screen& screen) const;
	void RenderSystemText(Screen& screen) const;
	void RenderInputBuffer(Screen& screen) const;

public:
	void Render(Screen& screen) const;

	void UpdateLevelName(const wstring& levelName);
	void UpdatePlayerName(const wstring& playerName);
	void UpdatePlayerLevel(int16 level);
	void UpdatePlayerHealth(int32 health, int32 maxHealth);
	void UpdatePlayerStatus(const Status& status);

	void EnqueueText(const wstring& text);
	void ClearText();

};

