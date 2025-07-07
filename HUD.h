#pragma once
#include "Object/BaseGameObject.h"
#include "Util/Type/CharacterInfo.h"
#include "Util/Type/EnumType.h"
#include "Util/Type/Gold.h"
#include "Util/Type/Health.h"
#include "Util/Type/StatusType.h"
#include "Util/Type/Experience.h"
#include "Item/BaseItem.h"
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
	wstring levelAreaName;

	wstring playerName;
	int16 playerLevel;
	Health health = Health::New(0);
	Status status;
	Experience experience;
	Gold gold;
	wstring weaponName;
	wstring armorName;
	vector<wstring> inventoryItems;
};

class HUD final
{
public:
	HUD() = default;
	~HUD() = default;

private:
	void RenderPlayerInfo(Screen& screen) const;
	void RenderSystemText(Screen& screen) const;
	void RenderInputBuffer(Screen& screen) const;

public:
	void Render(Screen& screen) const;
	void WriteLine(const wstring& text);
	void ClearText();

	void UpdateLevelName(const wstring& levelName);
	void UpdatePlayerName(const wstring& playerName);
	void UpdatePlayerLevel(int16 level);
	void UpdatePlayerHealth(const Health& health);
	void UpdatePlayerStatus(const Status& status);
	void UpdatePlayerExperience(const Experience& experience);
	void UpdatePlayerGold(const Gold& gold);
	void UpdateEquippedItem(const wstring& name, EItemType type);
	void UpdateInvetoryItems(const vector<BaseItem*>& items);

private:
	deque<wstring> m_systemTextQueue;
	FHudData m_hudData;

};

