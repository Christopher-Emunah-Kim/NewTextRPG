#pragma once
#include "../../Common.h"

class GameInstance;

class Health
{
private:
	Health(int32 currentAmount, int32 maxAmount)
		: m_currentAmount(currentAmount), m_maxAmount(maxAmount)
	{
	}

public:
	static Health New(int32 maxAmount)
	{
		if (maxAmount < 0)
		{
			throw invalid_argument("MaxHealth는 반드시 양수값이어야합니다.");
		}

		return Health(maxAmount, maxAmount);
	}

	Health Recover(int32 amount) const 
	{
		if (amount <= 0)
		{
			throw invalid_argument("회복량은 반드시 양수값이어야합니다.");
		}

		int32 newAmount = max(m_currentAmount + amount, m_maxAmount);

		return Health(newAmount, m_maxAmount);
	}

	Health TakeDamage(int32 amount) const
	{
		if (amount <= 0)
		{
			throw invalid_argument("회복량은 반드시 양수값이어야합니다.");
		}

		int32 newAmount = max(m_currentAmount - amount, 0);

		return Health(newAmount, m_maxAmount);
	}

	inline int32 GetCurrentAmount() const { return m_currentAmount; }
	inline int32 GetMaxAmount() const { return m_maxAmount; }
	inline bool IsFull() const { return m_currentAmount == m_maxAmount; }
	inline bool IsDead() const { return m_currentAmount <= 0; }

private:
	int32 m_currentAmount;
	int32 m_maxAmount;
};