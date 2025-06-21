#pragma once
#include "../Util/Singleton.h"
#include "../Object/Player.h"
#include "../Object/SystemTextDialog.h"


class GameInstance : public Singleton<GameInstance>
{
	friend class Singleton<GameInstance>;
	
private:
	GameInstance() = default;

public:
	virtual ~GameInstance() = default;

private:
	Player m_player;
	bool m_bIsPlayerInitialzed = false;
	SystemTextDialog* m_systemTextDialog;

public:
	void Init();

	bool IsPlayerInitialzed() const;
	void SetPlayerInitialize(bool bIsInitialized);

	void SetSystemTextDialog(SystemTextDialog* dialogObj);
	void DisplaySystemText(const string& text);

	inline Player& GetPlayer() noexcept { return m_player; }
	inline SystemTextDialog* GetSystemTextDialog() const { return m_systemTextDialog; }
};