#pragma once
#include "../../Common.h"

constexpr __int16 DEFAULT_ATTACK = 12;
constexpr __int16 DEFAULT_DEFENSE = 12;
constexpr __int16 DEFAULT_AGILITY = 12;
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

	/*CharacterStatus& operator=(const CharacterStatus& other)
	{
		if (this != &other)
		{
			const_cast<int16&>(attack) = other.attack;
			const_cast<int16&>(defense) = other.defense;
			const_cast<int16&>(agility) = other.agility;
		}
		return *this;
	}*/

private:
	const int16 attack;
	const int16 defense;
	const int16 agility;


public:
	const int16& GetAttack() const { return attack; }
	const int16& GetDefense() const { return defense; }
	const int16& GetAgility() const { return agility; }

	static Status NewStatus(const int16& atk, const int16& def, const int16& agi)
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

};
