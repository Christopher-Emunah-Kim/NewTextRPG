﻿#pragma once
#include "../Util/Singleton.h"
#include "../Character/Player.h"
#include "../HUD.h"


class GameInstance final : public Singleton<GameInstance>
{
public:
	GameInstance() = default;
	virtual ~GameInstance() = default;

	void WriteLine(const wstring& text = L"");
	void ClearText();
	void RenderHud(Screen& screen) const;
	void RequestShutdown();
	bool ShouldQuit() const;

	void UpdateLevelName(const wstring& levelName);
	void UpdatePlayerName(const wstring& playerName);
	void UpdatePlayerLevel(int16 level);
	void UpdatePlayerHealth(const Health& health);
	void UpdatePlayerStatus(const Status& status);
	void UpdatePlayerExperience(const Experience& experience);
	void UpdatePlayerGold(const Gold& gold);
	void UpdateEquippedItem(const wstring& name, EItemType type);
	void UpdateInvetoryItems(const vector<InventoryItem>& items);

	inline Player& GetPlayer() { return m_Player; }

private:
	HUD m_Hud;
	Player m_Player;
	bool m_ShouldQuit = false;
};