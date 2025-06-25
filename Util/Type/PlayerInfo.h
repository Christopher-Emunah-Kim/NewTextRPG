#pragma once
#include "../../Common.h"
#include "StatusType.h"
#include "LootType.h"
#include "../../Data/PlayerDataTablePerLevel.h"


struct FPlayerInfo
{
public:
	explicit FPlayerInfo(const int16& level)
	{
		FLevelProperties initialInfo = PlayerDataTablePerLevel::LoadPlayerLevelData(level);

		name = L"Default Player";
		playerLevel = level;
		health = initialInfo.maxHealthPerLevel;
		maxHealth = initialInfo.maxHealthPerLevel;
		status = Status::NewStatus(initialInfo.attackPerLevel, initialInfo.defensePerLevel, initialInfo.agilityPerLevel);
		experience = Experience();
		gold = Gold();
	}

public:
	wstring name;
	int16 playerLevel;
	int32 health;
	int32 maxHealth;

	Status status;
	Experience experience;
	Gold gold;

public:
	/*inline wstring GetName() const noexcept { return name; }
	inline Status GetStatus() const noexcept { return status; }
	inline Experience GetExperience() const noexcept { return experience; }
	inline int16 GetPlayerLevel() const noexcept { return playerLevel; }
	inline int16 GetAttack() const noexcept { return status.GetAttack(); }
	inline int16 GetDefense() const noexcept { return status.GetDefense(); }
	inline int16 GetAgility() const noexcept { return status.GetAgility(); }
	inline int16 GetGold() const noexcept { return gold.GetAmount(); }
	inline int32 GetCurrentHealth() const noexcept { return health; }*/
};