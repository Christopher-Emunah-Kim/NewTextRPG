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

EHealResult Healer::CheckHealAvailable(const Player& player) const
{
	if (false == player.CanAfford(m_healCost))
	{
		return EHealResult::NotEnoughGold;
	}

	if (player.IsFullHealth())
	{
		return EHealResult::AlreadyMaxHealth;
	}

	return EHealResult::RequestAccept;
}

void Healer::Heal(Player& player) const
{
	Health health = player.GetHealth();
	const int32 healAmount = health.GetMaxAmount() - health.GetCurrentAmount();

	player.Recover(healAmount);
	player.UseGold(m_healCost);
}
