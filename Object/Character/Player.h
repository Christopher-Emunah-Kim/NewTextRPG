#pragma once  
#include "BattleCharacter.h"  
#include "Util/Type/CharacterInfo.h"
#include "Util/Type/Health.h"
#include "Util/Type/Gold.h"


constexpr __int32 DEFAULT_OWNED_GOLD = 10000;


class Player final : public BattleCharacter  
{  

public:  
	Player();
	virtual ~Player() = default;

	virtual void Init() override;  

	void InitializeComponents();
	void RegisterNewLevelArea(BaseLevel* level);

	void TakeDamage(int32 amount);
	Health GetHealth() const;
	bool CanAfford(int32 cost) const;
	bool IsFullHealth() const;
	void Recover(int32 amount);

	bool UseGold(int32 amount);
	void GainGold(int32 amount);
	Gold GetGold() const;
	int32 GetGoldAmount() const;

	inline const FPlayerInfo& GetPlayerInfo() const noexcept { return m_playerInfo; }
	inline void SetPlayerInfo(const FPlayerInfo& info) { m_playerInfo = info; }

private:
	FPlayerInfo m_playerInfo;
	Gold m_gold;
};
