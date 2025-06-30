#pragma once  
#include "BattleCharacter.h"  
#include "../../Util/Type/CharacterInfo.h"

class Player final : public BattleCharacter  
{  
public:  

	Player();
	virtual ~Player() = default;

private:
	FPlayerInfo m_playerInfo;

public:
	virtual void Init() override;  

	void RegisterNewLevelArea(BaseLevel* level);

	void LevelUp();

	inline const FPlayerInfo& GetPlayerInfo() const noexcept { return m_playerInfo; }
	inline void SetPlayerInfo(const FPlayerInfo& info) { m_playerInfo = info; }
};
