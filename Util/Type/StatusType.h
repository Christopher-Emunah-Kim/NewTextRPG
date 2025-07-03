#pragma once
#include "../../Common.h"
#include "../../Data/PlayerDataTablePerLevel.h"

constexpr __int8 DEFAULT_LOWEST_DAMAGE = 5;


struct Status
{
	Status()
		: attack{ DEFAULT_ATTACK }, defense{ DEFAULT_DEFENSE }, agility{ DEFAULT_AGILITY }
	{
	}

	Status(int16 atk, int16 def, int16 agi)
		: attack{ atk }, defense{ def }, agility{ agi }
	{
	}

	Status& operator=(const Status& other)
	{
		if (this != &other)
		{
			const_cast<int16&>(attack) = other.attack;
			const_cast<int16&>(defense) = other.defense;
			const_cast<int16&>(agility) = other.agility;
		}
		return *this;
	}

	Status operator+(const Status& other) const
	{
		return Status(
			this->attack + other.attack,
			this->defense + other.defense,
			this->agility + other.agility
		);
	}

	Status& operator+=(const Status& other)
	{
		const_cast<int16&>(attack) += other.attack;
		const_cast<int16&>(defense) += other.defense;
		const_cast<int16&>(agility) += other.agility;
		return *this;
	}


	static Status NewStatus(int16 atk, int16 def, int16 agi)
	{
		return Status(atk, def, agi);
	}

	static Status AddStatus(const Status& self, const Status& other)
	{
		return Status(
			self.attack + other.attack,
			self.defense + other.defense,
			self.agility + other.agility
		);
	}

	static Status RemoveStatus(const Status& self, const Status& other)
	{
		return Status(
			self.attack - other.attack,
			self.defense - other.defense,
			self.agility - other.agility
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
		return L"공격력: " + to_wstring(attack) + L", 방어력: " + to_wstring(defense) + L", 민첩성 : " + to_wstring(agility);
	}

	const int16& GetAttack() const { return attack; }
	const int16& GetDefense() const { return defense; }
	const int16& GetAgility() const { return agility; }

private:
	const int16 attack;
	const int16 defense;
	const int16 agility;
};
