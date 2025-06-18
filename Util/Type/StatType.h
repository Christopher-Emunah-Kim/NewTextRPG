#pragma once
#include "../Common.h"


using namespace std;

enum class EStatType : uint8
{
	HP,
	ATTACK,
	DEFENSE,
	AGILITY,
	MAX_COUNT
};

enum class EModifierType : uint8
{
	ADD,
	SUBTRACT,
	MUTIFLY
};

struct Modifier
{
	EStatType targetStatType;
	EModifierType modifierType;
	int8 value = 0;
};

struct ModifierContainer
{
	wstring id;
	vector<Modifier> modifiers;
};

struct StatusValue
{
	int8 baseStatValue = 0;
	int8 bonusStatValue = 0;
	int16 finalStatValue = 0;
	bool bIsChanged = true;
};


struct Status
{
	unordered_map<EStatType, StatusValue> m_statsMap;
	unordered_map<wstring, ModifierContainer> m_modifierContainers;

	int16	GetStatValue(EStatType statType)
	{
		unordered_map<EStatType, StatusValue>::iterator it = m_statsMap.find(statType);
		
		if (it == m_statsMap.end())
		{
			return 0;
		}

		if (it->second.bIsChanged == false)
		{
			return it->second.finalStatValue;
		}

		int16 tempCalculatedValue = CalculateStatusValue(statType);
		it->second.finalStatValue = tempCalculatedValue;
		it->second.bIsChanged = false;

		return tempCalculatedValue;
	}

	void	AddModifierContainer(const ModifierContainer& container)
	{

	}

	void	RemoveModifierContainer(const wstring& id)
	{

	}

private:
	int16	CalculateStatusValue(EStatType statType) const
	{

	}

	void	SetChangeStatus(const ModifierContainer& container)
	{

	}
};
