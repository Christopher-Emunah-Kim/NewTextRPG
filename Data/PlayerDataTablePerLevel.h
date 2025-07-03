#pragma once
#include "../Common.h"


constexpr __int8 ADDITIONAL_EXPERIENCE_PER_LEVEL = 20;
constexpr __int8 ADDITIONAL_HEALTH_PER_LEVEL = 5;
constexpr __int8 ADDITIONAL_ATTACK_PER_LEVEL = 1;
constexpr __int8 ADDITIONAL_DEFENSE_PER_LEVEL = 1;
constexpr __int8 ADDITIONAL_AGILITY_PER_LEVEL = 1;
constexpr __int16 DEFAULT_ATTACK = 12;
constexpr __int16 DEFAULT_DEFENSE = 12;
constexpr __int16 DEFAULT_AGILITY = 12;

constexpr __int16 DEFAULT_LEVEL = 1;
constexpr __int16 DEFAULT_MAX_LEVEL = 100;
constexpr __int16 DEFAULT_PLAYER_MAX_EXPERIENCE = 100;
constexpr __int16 DEFAULT_CHARACTER_MAX_HEALTH = 100;

constexpr __int16 DEFAULT_OWNED_GOLD = 10000;


struct FLevelProperties
{
	int32 maxExperiencePerLevel;
	int32 maxHealthPerLevel;
	int16 attackPerLevel;
	int16 defensePerLevel;
	int16 agilityPerLevel;
};


extern FLevelProperties levelDataArray[100]; 


struct FPlayerDataTablePerLevel
{
	static void InitializeLevelData();
	
	static FLevelProperties LoadPlayerLevelData(int16 level);
	
	static int16 GetRequiredMaxExp(int16 level);
	
};

