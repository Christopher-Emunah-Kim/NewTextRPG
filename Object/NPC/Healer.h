#pragma once
#include "Common.h"

enum class EHealResult : uint8
{
	RequestAccept,
	NotEnoughGold,
	AlreadyMaxHealth,
	MAX_COUNT
};

class Player;

class Healer final
{
public:
	explicit Healer(int32 healCost);

	int32 GetHealCost() const;
	int32 Heal(Player& player) const;
	EHealResult CheckHealAvailable(const Player& player) const;

private:
	const int32 m_healCost;

};

