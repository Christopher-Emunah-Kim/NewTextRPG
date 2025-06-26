#pragma once
#include "../../Common.h"
#include "../../Data/PlayerDataTablePerLevel.h"
#include "StatusType.h"
#include "LootType.h"

struct FCharacterInfo
{
	explicit FCharacterInfo(int16 level)
		: name(L"Default Character"), characterLevel(level),description(L"Default Character Description")
	{ }

	wstring name;
	int16 characterLevel;
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



struct FPlayerInfo : public FCombatCharacterInfo
{
	explicit FPlayerInfo(int16 level)
		: FCombatCharacterInfo(level)
	{
		experience = Experience(0, FPlayerDataTablePerLevel::GetRequiredMaxExp(level));
		gold = Gold();
	}

	Experience experience;
	Gold gold;
};