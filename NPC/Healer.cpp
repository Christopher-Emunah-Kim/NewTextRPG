#include "Healer.h"
#include "Util/Type/Health.h"
#include "Character/Player.h"

Healer::Healer(int32 healCost)
	: m_healCost(healCost)
{
}

int32 Healer::GetHealCost() const
{
	return m_healCost;
}

expected<bool, wstring> Healer::HealPlayer(Player& player) const
{
	if (false == player.CanAfford(m_healCost))
	{
		return unexpected(wstring(L"골드가 부족합니다. 치유를 받을 수 없습니다. 필요 골드: " + to_wstring(m_healCost)
			+ L", 보유골드: " + to_wstring(player.GetGoldAmount())));
	}

	if (player.IsFullHealth())
	{
		return unexpected(wstring(L"치유사는 당신에게 이미 완벽한 상태이기에 치유가 필요하지 않다고 말합니다."));
	}

	const int32 healAmount = player.GetMaxHealth() - player.GetCurrentHealth();
	player.Recover(healAmount);
	player.UseGold(m_healCost);

	return true;
}
