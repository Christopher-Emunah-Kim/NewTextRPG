#include "Healer.h"
#include "Util/Type/Health.h"
#include "Object/Character/Player.h"

Healer::Healer(int32 healCost)
	: m_healCost(healCost)
{
}

int32 Healer::GetHealCost() const
{
	return m_healCost;
}

EHealResult Healer::HealPlayer(Player& player) const
{
	if (false == player.CanAfford(m_healCost))
	{
		return EHealResult::NotEnoughGold;
	}

	if (player.IsFullHealth())
	{
		return EHealResult::AlreadyMaxHealth;
	}

	const int32 healAmount = player.GetMaxHealth() - player.GetCurrentHealth();
	player.Recover(healAmount);
	player.UseGold(m_healCost);

	return EHealResult::RequestAccept;
}
