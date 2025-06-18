#pragma once
#include "../Common.h"

struct Experience
{
	Experience() = default;
	explicit Experience(int8 level) : m_level(level), m_currentExp(0) { }

private:
	int16 m_currentExp = 0;
	int8 m_level = 1;

	
	int16 GetRequiredExpForNextLevel() const
	{
		//TODO : LevelData에서 불러오기
		return 3 + (m_level - 1) * 5;
	}

public:
	bool AddExperience(int16 amount)
	{
		m_currentExp += amount;
		bool leveledUp = false;

		while (m_currentExp >= GetRequiredExpForNextLevel())
		{
			m_currentExp -= GetRequiredExpForNextLevel();
			m_level++;
			leveledUp = true;
		}
		return leveledUp;
	}
};



struct Gold
{
	Gold() = default;
	explicit Gold(int16 initialAmount) : m_amount(initialAmount) { }

private:
	int16 m_amount = 10000;


public:
	void AddGold(int16 amount)
	{
		int32 total = static_cast<int32>(m_amount) + amount;

		if (total > INT16_MAX) 
		{ 
			m_amount = INT16_MAX;
		}
		else 
		{
			m_amount = static_cast<int16>(total);
		}
	}

	bool RemoveGold(int16 amount)
	{
		if (m_amount < amount)
		{
			return false;
		}

		m_amount -= amount;
		
		return true;
	}
};
