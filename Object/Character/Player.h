#pragma once  
#include "BattleCharacter.h"  
#include "Util/Type/CharacterInfo.h"
#include "Util/Type/Health.h"
#include "Util/Type/Gold.h"
#include "Util/Type/Experience.h"
#include "Component/Equipment.h"
#include "Component/Inventory.h"


constexpr __int32 DEFAULT_OWNED_GOLD = 10000;


class Player final : public BattleCharacter  
{  
public:  
	Player();
	~Player() = default;

private:
	void LoadLevelPropertiesByLevel();

public:
	void Init() override;  

	void UpdatePlayerHUD();
	void RegisterNewLevelArea(BaseLevel* level);

	bool CanAfford(int32 cost) const;
	bool IsFullHealth() const;
	void Recover(int32 amount);
	bool UseGold(int32 amount);
	void GainGold(int32 amount);
	bool GainExperience(int32 exp);

	//int32 GetGoldAmount() const;
	Gold GetGold() const;
	Health GetHealth() const;
	Status GetTotalStatus() const;
	Experience GetExperience() const;
	Inventory& GetInventory();
	Equipment& GetEquipment();

private:
	Gold m_gold;
	Experience m_experience;
	Inventory m_inventory;
	Equipment m_equipment;
};
