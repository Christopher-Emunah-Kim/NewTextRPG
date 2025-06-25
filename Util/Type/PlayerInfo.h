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
		FLevelProperties initialInfo = FPlayerDataTablePerLevel::LoadPlayerLevelData(level);

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

};