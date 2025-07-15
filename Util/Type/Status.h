#pragma once
#include "../../Common.h"
#include "../../Data/PlayerDataTablePerLevel.h"

constexpr __int8 DEFAULT_LOWEST_DAMAGE = 5;


struct Status
{
	Status()
		: m_attack{ DEFAULT_ATTACK }, m_defense{ DEFAULT_DEFENSE }, m_agility{ DEFAULT_AGILITY }
	{
	}

	Status(int16 atk, int16 def, int16 agi)
		: m_attack{ atk }, m_defense{ def }, m_agility{ agi }
	{
	}

	Status& operator=(const Status& other)
	{
		if (this != &other)
		{
			m_attack = other.m_attack;
			m_defense = other.m_defense;
			m_agility = other.m_agility;
		}
		return *this;
	}

	Status operator+(const Status& other) const
	{
		return Status(
			m_attack + other.m_attack,
			m_defense + other.m_defense,
			m_agility + other.m_agility
		);
	}

	Status& operator+=(const Status& other)
	{
		m_attack += other.m_attack;
		m_defense += other.m_defense;
		m_agility += other.m_agility;
		return *this;
	}


	static Status NewStatus(int16 atk, int16 def, int16 agi)
	{
		return Status(atk, def, agi);
	}

	static Status AddStatus(const Status& self, const Status& other)
	{
		return Status(
			self.m_attack + other.m_attack,
			self.m_defense + other.m_defense,
			self.m_agility + other.m_agility
		);
	}

	static Status RemoveStatus(const Status& self, const Status& other)
	{
		return Status(
			self.m_attack - other.m_attack,
			self.m_defense - other.m_defense,
			self.m_agility - other.m_agility
		);
	}

	static int32 CalculateDamage(const Status& self, const Status& other)
	{
		int32 damage = other.GetAttack() - self.GetDefense();

		if (damage <= 0)
		{
			return DEFAULT_LOWEST_DAMAGE;
		}
		else
		{
			return damage;
		}
	}

	wstring ToString() const
	{
		return L"공격력: " + to_wstring(m_attack) + L", 방어력: " + to_wstring(m_defense) + L", 민첩성 : " + to_wstring(m_agility);
	}

	const int16& GetAttack() const { return m_attack; }
	const int16& GetDefense() const { return m_defense; }
	const int16& GetAgility() const { return m_agility; }

private:
	int16 m_attack;
	int16 m_defense;
	int16 m_agility;
};
