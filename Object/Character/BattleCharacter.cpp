#include "BattleCharacter.h"
#include "../../Core/GameInstance.h"
#include "../../Component/BattleComponent.h"


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

	if (!HasComponentType<BattleComponent>())
	{
		AddComponent(new BattleComponent(this));
	}
}

void BattleCharacter::Interact(BaseCharacter* other)
{
	BattleCharacter* battleTarget = dynamic_cast<BattleCharacter*>(other);
	if (battleTarget && IsAlive() && battleTarget->IsAlive())
	{
		BattleComponent* battleComp = GetComponentsByType<BattleComponent>();
		if (battleComp)
		{
			battleComp->InitiateBattle(battleTarget);
		}
		else
		{
			Attack(battleTarget);
		}
	}
}

void BattleCharacter::Attack(BattleCharacter* target)
{
	if (nullptr == target)
	{
		return;
	}

	int32 clculatedDamage = CalculateDamage(target);
	GameInstance::GetInstance()->DisplaySystemText(GetName() + L"가(이) " + target->GetName() + L" 을(를) 공격합니다!");

	target->TakeDamage(clculatedDamage);
}

void BattleCharacter::TakeDamage(const int32& damage)
{
	if (damage <= 0)
	{
		return;
	}

	m_battleCharacterInfo.health -= damage;

	if (m_battleCharacterInfo.health < 0)
	{
		m_battleCharacterInfo.health = 0;
	}

	GameInstance::GetInstance()->DisplaySystemText(GetName() + L"가(이) " + to_wstring(damage) + L" 의 피해를 입었습니다.");
}

bool BattleCharacter::IsAlive() const
{
	return m_battleCharacterInfo.health > 0;
}

int32 BattleCharacter::CalculateDamage(BattleCharacter* target) const
{
	int32 damage = m_battleCharacterInfo.status.GetAttack() - target->GetStatus().GetDefense();

	if (damage > 0)
	{
		return damage;
	}
	else
	{
		return DEFAULT_DAMAGE;
	}
}

void BattleCharacter::SetHealth(const int32& health)
{
	m_battleCharacterInfo.health = health;
	if (m_battleCharacterInfo.health > m_battleCharacterInfo.maxHealth)
	{
		m_battleCharacterInfo.health = m_battleCharacterInfo.maxHealth;
	}
}

void BattleCharacter::SetMaxHealth(const int32& maxHealth)
{
	m_battleCharacterInfo.maxHealth = maxHealth;
}

void BattleCharacter::SetStatus(const Status& status)
{
	m_battleCharacterInfo.status = status;
}
