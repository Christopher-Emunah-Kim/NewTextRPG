#pragma once
#include "../Util/Singleton.h"
#include "../Object/Character/Player.h"
#include "../Object/UI/HUDUI.h"


class GameInstance final : public Singleton<GameInstance>
{
private:

public:
	GameInstance() = default;
	virtual ~GameInstance() = default;

private:
	HUDUI* m_HUDUI = nullptr;
	Player m_Player;

public:
	inline Player& GetPlayer() { return m_Player; }


	void DisplaySystemText(const wstring& text);

	//void ChangeLevelAreaSettings(BaseLevel* newLevel);
	void SetHUDUI(HUDUI* playerInfoObj);
	inline HUDUI* GetHUDUI() noexcept { return m_HUDUI; }
};