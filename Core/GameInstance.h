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
	bool m_bIsPlayerInitialzed = false;

public:
	void Init();

	
	bool IsPlayerInitialzed() const;
	void SetPlayerInitialize(bool bIsInitialized);

	void DisplaySystemText(const wstring& text);
	void ChangeLevelAreaSettings(BaseLevel* newLevel);

	void SetHUDUI(HUDUI* playerInfoObj);
	inline HUDUI* GetHUDUI() noexcept { return m_HUDUI; }
};