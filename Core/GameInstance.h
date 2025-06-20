#pragma once
#include "../Util/Singleton.h"
#include "../Object/Player.h"


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

public:
	void Init();
	bool IsPlayerInitialzed() const;
	void SetPlayerInitialize(bool bIsInitialized);

	inline Player& GetPlayer() noexcept { return m_player; }
};