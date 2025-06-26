#pragma once
#include "../../Common.h"
#include "../../Data/PlayerDataTablePerLevel.h"
#include "StatusType.h"
#include "LootType.h"

struct FCharacterInfo
{
	explicit FCharacterInfo(int16 level)
		: name(L"Default Character"), level(level),	description(L"Default Character Description")
	{ }

	wstring name;
	int16 level;
	wstring description;
};

struct FCombatCharacterInfo : public FCharacterInfo
{
	explicit FCombatCharacterInfo(int16 level)
		: FCharacterInfo(level)
	{
		FLevelProperties initialInfo = FPlayerDataTablePerLevel::LoadPlayerLevelData(level);

		health = initialInfo.maxHealthPerLevel;
		maxHealth = initialInfo.maxHealthPerLevel;
		status = Status::NewStatus(initialInfo.attackPerLevel, initialInfo.defensePerLevel, initialInfo.agilityPerLevel);
	}
	
	int32 health;
	int32 maxHealth;
	Status status;
};


struct FPlayerInfo
{
	explicit FPlayerInfo(int16 level)
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

	wstring name;
	int16 playerLevel;
	int32 health;
	int32 maxHealth;

	Status status;
	Experience experience;
	Gold gold;

};