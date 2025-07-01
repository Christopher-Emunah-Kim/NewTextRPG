#include "BattleCharacter.h"
#include "../../Core/GameInstance.h"
#include "../../Util/BattleSystem.h"
#include "../../Level/DungeonLevel.h"


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

void BattleCharacter::Interact(BaseCharacter* other)
{
	BattleCharacter* battleTarget = dynamic_cast<BattleCharacter*>(other);
	if (battleTarget && IsAlive() && battleTarget->IsAlive())
	{
		BattleSystem::StartBattle(this, battleTarget);
	}
}

void BattleCharacter::Attack(BattleCharacter* target)
{
	if (nullptr == target)
	{
		return;
	}

	int32 clculatedDamage = CalculateDamage(target);
	GameInstance::GetInstance()->EnqueueText(L"");
	GameInstance::GetInstance()->EnqueueText(GetName() + L"가(이) " + target->GetName() + L" 을(를) 공격합니다!");
	GameInstance::GetInstance()->EnqueueText(L"");

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
	GameInstance::GetInstance()->EnqueueText(L"");
	GameInstance::GetInstance()->EnqueueText(GetName() + L"가(이) " + to_wstring(damage) + L" 의 피해를 입었습니다.");
	GameInstance::GetInstance()->EnqueueText(L"");
}

bool BattleCharacter::IsAlive() const
{
	return m_battleCharacterInfo.health > 0;
}

int32 BattleCharacter::CalculateDamage(BattleCharacter* target) const
{
	int32 damage = m_battleCharacterInfo.status.GetAttack() - target->GetBattleCharacterInfo().status.GetDefense();

	if (damage > 0)
	{
		return damage;
	}
	else
	{
		return DEFAULT_DAMAGE;
	}
}
