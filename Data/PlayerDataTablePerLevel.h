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


static FLevelProperties levelDataArray[100]; 


struct FPlayerDataTablePerLevel
{
	void InitializeLevelData()
	{
		for (int i = 0; i < DEFAULT_MAX_LEVEL; ++i)
		{
			levelDataArray[i].maxExperiencePerLevel = DEFAULT_PLAYER_MAX_EXPERIENCE + (i * ADDITIONAL_EXPERIENCE_PER_LEVEL); 
			levelDataArray[i].maxHealthPerLevel = DEFAULT_CHARACTER_MAX_HEALTH + (i * ADDITIONAL_HEALTH_PER_LEVEL); 

			levelDataArray[i].attackPerLevel = static_cast<int16>(DEFAULT_ATTACK * pow(1.05, i));
			levelDataArray[i].defensePerLevel = static_cast<int16>(DEFAULT_DEFENSE * pow(1.05, i));
			levelDataArray[i].agilityPerLevel = static_cast<int16>(DEFAULT_AGILITY * pow(1.05, i));
		}
		//TODO : 레벨데이터 csv파일에서 값 가져와 세팅하기
	}

	static FLevelProperties LoadPlayerLevelData(int16 level)
	{
		if (level < DEFAULT_LEVEL || level > DEFAULT_MAX_LEVEL)
		{
			cout << "Level must be between 1 and 100." << endl;

			return FLevelProperties{
				DEFAULT_PLAYER_MAX_EXPERIENCE,
				DEFAULT_CHARACTER_MAX_HEALTH,
				DEFAULT_ATTACK,
				DEFAULT_DEFENSE,
				DEFAULT_AGILITY };
		}
		return levelDataArray[level - 1];
	}

	static int16 GetRequiredMaxExp(const int16 level)  
	{
		if (level < DEFAULT_LEVEL || level > DEFAULT_MAX_LEVEL)
		{
			cout << "Level must be between 1 and 100." << endl;
			return DEFAULT_MAX_LEVEL;
		}

		FLevelProperties info = LoadPlayerLevelData(level);
		return info.maxExperiencePerLevel;
	}
};

