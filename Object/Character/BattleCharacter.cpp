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

	int32 clculatedDamage = m_battleCharacterInfo.status.CalculateDamage(this->m_battleCharacterInfo.status, target->m_battleCharacterInfo.status);
	GameInstance::GetInstance()->WriteLine(L"");
	GameInstance::GetInstance()->WriteLine(GetName() + L"가(이) " + target->GetName() + L" 을(를) 공격합니다!");
	GameInstance::GetInstance()->WriteLine(L"");

	target->m_battleCharacterInfo.health = target->m_battleCharacterInfo.health.TakeDamage(clculatedDamage);
	GameInstance::GetInstance()->WriteLine(L"");
	GameInstance::GetInstance()->WriteLine(target->GetName() + L"가(이) " + to_wstring(clculatedDamage) + L" 의 피해를 입었습니다.");
	GameInstance::GetInstance()->WriteLine(L"");
}


bool BattleCharacter::IsAlive() const
{
	return false == m_battleCharacterInfo.health.IsDead();
}

