#pragma once
#include "Common.h"

enum class EHealResult
{
	RequestAccept,
	NotEnoughGold,
	AlreadyMaxHealth
};

class Player;

class Healer final
{
public:
	explicit Healer(int32 healCost);

	int32 GetHealCost() const;
	void Heal(Player& player) const;
	EHealResult CheckHealAvailable(const Player& player) const;

private:
	const int32 m_healCost;

};

