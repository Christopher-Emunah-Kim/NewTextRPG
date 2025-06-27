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
	Player m_player;
	HUDUI* m_HUDUI = nullptr;
	bool m_bIsPlayerInitialzed = false;

public:
	void Init();

	bool IsPlayerInitialzed() const;
	void SetPlayerInitialize(bool bIsInitialized);

	//void SetSystemTextDialog(SystemTextDialog* systemDialogObj);
	void DisplaySystemText(const wstring& text);
	void ChangeLevelAreaSettings(BaseLevel* newLevel);

	void SetHUDUI(HUDUI* playerInfoObj);
	void UpdatePlayerInfo();

	inline Player& GetPlayer() noexcept { return m_player; }
	//inline SystemTextDialog* GetSystemTextDialog() noexcept { return m_systemTextDialog; }
	inline HUDUI* GetHUDUI() noexcept { return m_HUDUI; }
};