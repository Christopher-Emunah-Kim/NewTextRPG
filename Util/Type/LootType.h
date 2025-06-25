#pragma once
#include "../../Common.h"
#include "../../Data/PlayerDataTablePerLevel.h"



struct Experience
{
	explicit Experience()
		: m_currentExp(0), m_levelMaxExp(DEFAULT_PLAYER_MAX_EXPERIENCE)
	{ }

private:
	int16 m_currentExp;
	int16 m_levelMaxExp;


public:
	int16 AddExperience(int16 amount, int16 currentLevel)
	{
		m_currentExp += amount;
		m_levelMaxExp = FPlayerDataTablePerLevel::GetRequiredMaxExp(currentLevel);
		int16 levelUpCount = 0;


		while (m_currentExp >= m_levelMaxExp)
		{
			m_currentExp -= m_levelMaxExp;
			++currentLevel;
			++levelUpCount;
		}

		return levelUpCount;
	}

	void SetMaxExp(const int16& amount)
	{
		m_levelMaxExp = amount;
	}

	inline const int16& GetCurrentExp() const noexcept { return m_currentExp; }
	inline const int16& GetMaxExp() const noexcept { return m_levelMaxExp; }
};



struct Gold
{
	explicit Gold() 
		: m_amount(DEFAULT_OWNED_GOLD) { }

private:
	int16 m_amount;


public:
	void GainGold(int16 amount)
	{
		int16 total = m_amount + amount;

		if (total > INT16_MAX) 
		{ 
			m_amount = INT16_MAX;
		}
		else 
		{
			m_amount = total;
		}
	}

	bool UseGold(int16 amount)
	{
		if (m_amount < amount)
		{
			return false;
		}

		m_amount -= amount;
		
		return true;
	}

	inline int16 GetAmount() const noexcept { return m_amount; }
};
