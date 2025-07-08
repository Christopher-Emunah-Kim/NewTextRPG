#pragma once  
#include "BattleCharacter.h"  
#include "Util/Type/CharacterInfo.h"
#include "Util/Type/Health.h"
#include "Util/Type/Gold.h"
#include "Util/Type/Experience.h"
#include "Component/Equipment.h"
#include "Component/Inventory.h"


constexpr __int32 DEFAULT_OWNED_GOLD = 10000;

class BaseItem;

class Player final : public BattleCharacter  
{  
public:  
	Player();
	~Player() = default;

private:
	void LoadLevelPropertiesByLevel();
	void UpdatePlayerHUD();

public:
	void Init() override;  
	void RegisterNewLevelArea(BaseLevel* level);

	bool IsFullHealth() const;
	void Recover(int32 amount);
	int32 GetCurrentHealth() const;
	int32 GetMaxHealth() const;

	int32 GetGoldAmount() const;
	bool CanAfford(int32 cost) const;
	bool UseGold(int32 amount);
	void GainGold(int32 amount);
	bool GainExperience(int32 exp);

	const vector<BaseItem*> GetInventoryItems() const;
	void RemoveItemFromInventory(int32 itemId, int16 count = 1);
	bool AddItemToInventory(BaseItem* item);
	BaseItem* GetItemFromInventory(int32 itemId) const;

	bool Equip(BaseItem* item);
	BaseItem* GetEquippedItem(EItemType itemType) const;
	Status GetTotalPlayerStatus() const;

	Gold GetGoldForHUD() const;
	Health GetHealthForHUD() const;
	Experience GetExperienceForHUD() const;

private:
	Gold m_gold;
	Experience m_experience;
	Inventory m_inventory;
	Equipment m_equipment;
};
