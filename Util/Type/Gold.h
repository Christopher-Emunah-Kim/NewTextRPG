#pragma once
#include "../../Common.h"
#include "../../Data/PlayerDataTablePerLevel.h"

class Gold
{
public:
	explicit Gold(int32 amount = 0)
		: m_amount(amount)
	{
		if (amount < 0)
		{
			throw invalid_argument("생성된 골드가 음수값입니다");
		}
	}

	Gold Gain(int32 amount) const 
	{ 
		return Gold(m_amount + amount); 
	}

	Gold Use(int32 cost) const
	{
		if (false == CanAfford(cost))
		{
			return Gold(0);
		}

		return Gold(m_amount - cost);
	}

	bool operator==(const Gold& other) const { return m_amount == other.m_amount; }
	bool operator!=(const Gold& other) const { return !(*this == other); }

	inline int32 GetAmount() const noexcept { return m_amount; }
	inline bool CanAfford(int32 cost) const { return m_amount >= cost; }

private:
	int32 m_amount;

};