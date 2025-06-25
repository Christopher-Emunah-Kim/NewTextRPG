#pragma once
#include "../Util/Singleton.h"
#include "../Object/Player.h"
#include "../Object/UI/SystemTextDialog.h"
#include "../Object/UI/PlayerInfoDialog.h"


class GameInstance : public Singleton<GameInstance>
{
private:

public:
	GameInstance() = default;
	virtual ~GameInstance() = default;

private:
	Player m_player;
	SystemTextDialog* m_systemTextDialog = nullptr;
	PlayerInfoDialog* m_playerInfoDialog = nullptr;
	bool m_bIsPlayerInitialzed = false;

public:
	void Init();

	bool IsPlayerInitialzed() const;
	void SetPlayerInitialize(bool bIsInitialized);

	void SetSystemTextDialog(SystemTextDialog* systemDialogObj);
	void DisplaySystemText(const wstring& text);
	void ChangeLevelAreaSettings(BaseLevel* newLevel);

	void SetPlayerInfoDialog(PlayerInfoDialog* playerInfoObj);
	void UpdatePlayerInfo();

	inline Player& GetPlayer() noexcept { return m_player; }
	inline SystemTextDialog* GetSystemTextDialog() noexcept { return m_systemTextDialog; }
	inline PlayerInfoDialog* GetPlayerInfoDialog() noexcept { return m_playerInfoDialog; }
};