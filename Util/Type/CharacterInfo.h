#pragma once
#include "../../Common.h"
#include "../../Data/PlayerDataTablePerLevel.h"
#include "Status.h"
#include "Health.h"


struct Experience;

struct FCharacterInfo
{
	explicit FCharacterInfo(int16 level)
		: name(L"최강워로드"), characterLevel(level),description(L"스칼드로서의 삶에 회한을 느낀 전사")
	{ }

	wstring name;
	int16 characterLevel;
	wstring description;
};


struct FBattleCharacterInfo : public FCharacterInfo
{
	explicit FBattleCharacterInfo(int16 level)
		: FCharacterInfo(level), health(Health::New(0))
	{
		FLevelProperties initialInfo = PlayerLevelPropertiesTable::GetInstance()->LoadPlayerLevelData(level);

		health = Health::New(initialInfo.maxHealthPerLevel);
		status = Status::NewStatus(initialInfo.attackPerLevel, initialInfo.defensePerLevel, initialInfo.agilityPerLevel);
	}
	
	Health health;
	Status status;
};


struct FMonsterInfo : public FBattleCharacterInfo
{
	explicit FMonsterInfo(int16 level)
		: FBattleCharacterInfo(level), dropGold(0), dropExperience(0), monsterId(0)
	{
	}

	FMonsterInfo()
		: FBattleCharacterInfo(1), dropGold(0), dropExperience(0), monsterId(0)
	{
	}

	int16 dropGold;
	int16 dropExperience;
	int32 monsterId;
};