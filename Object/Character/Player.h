#pragma once  
#include "BattleCharacter.h"  
#include "Util/Type/CharacterInfo.h"
#include "Util/Type/Health.h"
#include "Util/Type/Gold.h"
#include "Util/Type/Experience.h"
#include "Component/Equipment.h"
#include "Component/Inventory.h"


constexpr __int32 DEFAULT_OWNED_GOLD = 10000;

enum class EPlayerHandleItemResult
{
	NONE,
	Equipped,
	AddToInventory,
	InventoryFull,
	ItemNullPtr,
	NotUsuableItem,
	UseItem,
	InvalidItemType
};

//class BaseItem;
class InventoryItem;

class Player final : public BattleCharacter  
{  
public:  
	Player();
	virtual ~Player();

private:
	void LoadLevelPropertiesByLevel();
	void UpdatePlayerHUD();

public:
	virtual void Init() override;  
	virtual void Release() override;

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

	bool AddItemToInventory(int32 itemId, int16 count = 1);
	void RemoveItemFromInventory(int32 itemId, int16 count = 1);
	const vector<InventoryItem>& GetInventoryItems() const;
	const InventoryItem* GetItemFromInventory(int32 itemId) const;
	EPlayerHandleItemResult HandlePurchasedItem(InventoryItem item);
	EPlayerHandleItemResult HandleOwnedItem(const InventoryItem* item);

	bool Equip(int32 itemId);
	int32 GetEquippedItem(EItemType itemType) const;
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
