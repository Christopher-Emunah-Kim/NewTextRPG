#pragma once
#include "../Util/Singleton.h"
#include "../Object/Character/Player.h"
#include "../HUD.h"


class GameInstance final : public Singleton<GameInstance>
{
public:
	GameInstance() = default;
	virtual ~GameInstance() = default;

private:
	HUD m_Hud;
	Player m_Player;

public:
	void UpdateLevelName(const wstring& levelName);
	void UpdatePlayerName(const wstring& playerName);
	void UpdatePlayerLevel(int16 level);
	void UpdatePlayerHealth(int32 health, int32 maxHealth);
	void UpdatePlayerStatus(const Status& status);
	void UpdatePlayerExperience(const Experience& experience);
	void UpdatePlayerGold(const Gold& gold);
	void UpdateEquippedItem(const wstring& name, EItemType type);
	void UpdateInvetoryItems(const wstring& name);

	void EnqueueText(const wstring& text);
	void ClearText();

	void RenderHud(Screen& screen) const;

	void SyncAllHudData(const wstring& levelName, const wstring& playerName, int16 level,
		int32 health, int32 maxHealth, const Status& status, const Experience& experience,
		const Gold& gold, const wstring& weaponName, EItemType weaponType, const wstring& armorName, EItemType armorType,
		const vector<wstring>& inventoryItems);

	inline Player& GetPlayer() { return m_Player; }
};