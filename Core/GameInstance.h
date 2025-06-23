#pragma once
#include "../Util/Singleton.h"
#include "../Object/Player.h"
#include "../Object/UI/SystemTextDialog.h"
#include "../Object/UI/PlayerInfoDialog.h"


class GameInstance : public Singleton<GameInstance>
{
	friend class Singleton<GameInstance>;
	
private:
	GameInstance() = default;

public:
	virtual ~GameInstance() = default;

private:
	Player m_player;
	SystemTextDialog* m_systemTextDialog;
	PlayerInfoDialog* m_playerInfoDialog;
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
	inline SystemTextDialog* GetSystemTextDialog() const { return m_systemTextDialog; }
	inline PlayerInfoDialog* GetPlayerInfoDialog() const { return m_playerInfoDialog; }
};