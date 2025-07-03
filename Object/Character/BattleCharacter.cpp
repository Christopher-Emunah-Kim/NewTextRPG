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
	GameInstance::GetInstance()->WriteLine(L"");
	GameInstance::GetInstance()->WriteLine(GetName() + L"가(이) " + target->GetName() + L" 을(를) 공격합니다!");
	GameInstance::GetInstance()->WriteLine(L"");

	target->TakeDamage(clculatedDamage);
}

void BattleCharacter::TakeDamage(int32 damage)
{
	if (damage <= 0)
	{
		return;
	}

	//TODO Health 사용방식이 이게 맞나?
	m_battleCharacterInfo.health.TakeDamage(damage);


	if (m_battleCharacterInfo.health.GetCurrentAmount() < 0)
	{
		m_battleCharacterInfo.health.New(0);
	}

	GameInstance::GetInstance()->WriteLine(L"");
	GameInstance::GetInstance()->WriteLine(GetName() + L"가(이) " + to_wstring(damage) + L" 의 피해를 입었습니다.");
	GameInstance::GetInstance()->WriteLine(L"");
}

bool BattleCharacter::IsAlive() const
{
	return false == m_battleCharacterInfo.health.IsDead();
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
