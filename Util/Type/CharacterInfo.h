#pragma once
#include "../../Common.h"
#include "../../Data/PlayerDataTablePerLevel.h"
#include "StatusType.h"


struct FCharacterInfo
{
	explicit FCharacterInfo(int16 level)
		: name(L"Default Character"), characterLevel(level),description(L"Default Character Description")
	{ }

	wstring name;
	int16 characterLevel;
	wstring description;
};



struct FBattleCharacterInfo : public FCharacterInfo
{
	explicit FBattleCharacterInfo(int16 level)
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


struct Experience;
struct Gold;

struct FPlayerInfo : public FBattleCharacterInfo
{
	explicit FPlayerInfo(int16 level)
		: FBattleCharacterInfo(level)
	{
		experience = Experience(0, FPlayerDataTablePerLevel::GetRequiredMaxExp(level));
		gold = Gold();
	}

	Experience experience;
	Gold gold;
};


struct FMonsterInfo : public FBattleCharacterInfo
{
	explicit FMonsterInfo(int16 level)
		: FBattleCharacterInfo(level), dropGold(level * 5), dropExperience(level * 10), dropItemId(10000)
	{
		//TODO 몬스터 테이블에서 드랍정보 불러오기

	}

	int16 dropGold;
	int16 dropExperience;
	int32 dropItemId;
};