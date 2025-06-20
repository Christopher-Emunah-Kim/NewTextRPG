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

//이후 플레이어로 이동
constexpr __int16 DEFAULT_PLAYER_MAX_EXPERIENCE = 100;
constexpr __int16 DEFAULT_CHARACTER_MAX_HEALTH = 100;


struct FLevelProperties
{
	int32 maxExperiencePerLevel;
	int32 maxHealthPerLevel;
	int16 attackPerLevel;
	int16 defensePerLevel;
	int16 agilityPerLevel;
};


static FLevelProperties levelDataArray[100]; // Array to hold level data for 100 levels


struct PlayerDataTablePerLevel
{
	void InitializeLevelData()
	{
		// Initialize level data for 100 levels
		for (int i = 0; i < 100; ++i)
		{
			levelDataArray[i].maxExperiencePerLevel = DEFAULT_PLAYER_MAX_EXPERIENCE + (i * ADDITIONAL_EXPERIENCE_PER_LEVEL); // Example formula
			levelDataArray[i].maxHealthPerLevel = DEFAULT_CHARACTER_MAX_HEALTH + (i * ADDITIONAL_HEALTH_PER_LEVEL); // Example formula

			levelDataArray[i].attackPerLevel = static_cast<int16>(DEFAULT_ATTACK * pow(1.05, i));
			levelDataArray[i].defensePerLevel = static_cast<int16>(DEFAULT_DEFENSE * pow(1.05, i));
			levelDataArray[i].agilityPerLevel = static_cast<int16>(DEFAULT_AGILITY * pow(1.05, i));
		}
		//TODO : 레벨데이터 csv파일에서 값 가져와 세팅하기
	}

	FLevelProperties LoadLevelData(int16 level)
	{
		if (level < 1 || level > 100)
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
};

