#pragma once
#include "Common.h"


class Player;

class Healer final
{
public:
	explicit Healer(int32 healCost);

	int32 GetHealCost() const;
	expected<bool, wstring> HealPlayer(Player& player) const;

private:
	const int32 m_healCost;

};

