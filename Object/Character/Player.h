#pragma once  
#include "BattleCharacter.h"  
#include "Util/Type/CharacterInfo.h"
#include "Util/Type/Health.h"
#include "Util/Type/Gold.h"
#include "Util/Type/Experience.h"


constexpr __int32 DEFAULT_OWNED_GOLD = 10000;


class Player final : public BattleCharacter  
{  
public:  
	Player();
	virtual ~Player() = default;

private:
	void LoadLevelPropertiesByLevel();

public:

	virtual void Init() override;  

	void InitializeComponents();
	void RegisterNewLevelArea(BaseLevel* level);

	bool CanAfford(int32 cost) const;
	bool IsFullHealth() const;
	void Recover(int32 amount);
	Health GetHealth() const;

	bool UseGold(int32 amount);
	void GainGold(int32 amount);
	int32 GetGoldAmount() const;
	Gold GetGold() const;

	bool GainExperience(int32 exp);
	Status GetTotalStatus() const;
	
private:
	Gold m_gold;
	Experience m_experience;
};
