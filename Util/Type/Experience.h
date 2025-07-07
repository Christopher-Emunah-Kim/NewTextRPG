#pragma once
#include "../../Common.h"
#include "../../Data/PlayerDataTablePerLevel.h"




struct Experience
{
	explicit Experience(const int16& exp = 0, const int16& maxExp = 100)
		: m_currentExp(0), m_levelMaxExp(DEFAULT_PLAYER_MAX_EXPERIENCE)
	{ }

	int16 AddExperience(int16 amount, int16 currentLevel)
	{
		m_currentExp += amount;
		m_levelMaxExp = PlayerLevelPropertiesTable::GetInstance()->GetRequiredMaxExp(currentLevel);
		int16 levelUpCount = 0;


		while (m_currentExp >= m_levelMaxExp)
		{
			m_currentExp -= m_levelMaxExp;
			++levelUpCount;
			++currentLevel;
			m_levelMaxExp = PlayerLevelPropertiesTable::GetInstance()->GetRequiredMaxExp(currentLevel);
		}

		return levelUpCount;
	}

	void SetMaxExp(const int16& amount)
	{
		m_levelMaxExp = amount;
	}

	inline int16 GetCurrentExp() const noexcept { return m_currentExp; }
	inline int16 GetMaxExp() const noexcept { return m_levelMaxExp; }

private:
	int16 m_currentExp;
	int16 m_levelMaxExp;
};




