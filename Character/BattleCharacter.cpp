#include "BattleCharacter.h"


BattleCharacter::BattleCharacter(BaseLevel* level, const wstring& tag)
	: BaseCharacter(level, tag), m_battleCharacterInfo(DEFAULT_LEVEL)
{
}

BattleCharacter::~BattleCharacter()
{
}

void BattleCharacter::Init()
{
	BaseCharacter::Init();
}

void BattleCharacter::Attack(BattleCharacter* target)
{
	if (nullptr == target)
	{
		return;
	}

	int32 clculatedDamage = m_battleCharacterInfo.status.CalculateDamage(this->m_battleCharacterInfo.status, target->m_battleCharacterInfo.status);

	target->m_battleCharacterInfo.health = target->m_battleCharacterInfo.health.TakeDamage(clculatedDamage);
}


bool BattleCharacter::IsAlive() const
{
	return false == m_battleCharacterInfo.health.IsDead();
}

