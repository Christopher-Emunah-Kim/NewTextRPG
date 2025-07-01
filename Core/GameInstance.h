#pragma once
#include "../Util/Singleton.h"
#include "../Object/Character/Player.h"
#include "../Object/UI/HUD.h"


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

	void EnqueueText(const wstring& text);
	void ClearText();

	void RenderHud(Screen& screen) const;

	inline Player& GetPlayer() { return m_Player; }
};