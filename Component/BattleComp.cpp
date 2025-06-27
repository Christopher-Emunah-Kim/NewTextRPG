#include "BattleComp.h"
#include "../Util/OutputSystem.h"

BattleComp::BattleComp(BaseGameObject* owner, int32 order)
	: BaseComponent(owner, order), m_currentTarget(nullptr), m_bIsBattleActive(false), m_bIsPlayerTurn(false)
{
	m_owner = dynamic_cast<BattleCharacter*>(owner);
	if (m_owner == nullptr)
	{
		OutputSystem::PrintErrorMsg(L"BattleComponent는 BattleCharacter에만 장착가능합니다.");
	}
}

BattleComp::~BattleComp()
{
}

void BattleComp::InitiateBattle(BattleCharacter* target)
{
	if (target == nullptr || m_owner == nullptr)
	{
		return;
	}
	m_currentTarget = target;
	m_bIsBattleActive = true;


	GameInstance::GetInstance()->DisplaySystemText(m_owner->GetName() + L"와(과" + target->GetName() + L"가(이) 전투를 시작합니다.");

	m_bIsPlayerTurn = DetermineFirstAttacker();

	ProcessBattleTurn();
}

void BattleComp::EndBattle()
{
	if (false == m_bIsBattleActive)
	{
		return;
	}

	HandleBattleRewards();

	m_bIsBattleActive = false;
	m_currentTarget = nullptr;

	GameInstance::GetInstance()->DisplaySystemText(L"전투가 종료되었습니다.");
}

void BattleComp::ProcessBattleTurn()
{
	if (false == m_bIsBattleActive || nullptr == m_currentTarget || nullptr == m_owner)
	{
		return;
	}

	ExecuteAttack();

	if (CheckBattleEnd())
	{
		EndBattle();
		return;
	}

	m_bIsPlayerTurn = !m_bIsPlayerTurn;

	if (false == m_bIsPlayerTurn)
	{
		ExecuteAttack();

		if (CheckBattleEnd())
		{
			EndBattle();
			return;
		}

		m_bIsPlayerTurn = true;
	}
}

bool BattleComp::DetermineFirstAttacker()
{
	if (nullptr == m_currentTarget || nullptr == m_owner)
	{
		return true;
	}

	int16 ownerAgility = m_owner->GetStatus().GetAgility();
	int16 targetAgility = m_currentTarget->GetStatus().GetAgility();

	if (ownerAgility >= targetAgility)
	{
		GameInstance::GetInstance()->DisplaySystemText(m_owner->GetName() + L"가 먼저 공격을 시도합니다.");
		return true;
	}
	else
	{
		GameInstance::GetInstance()->DisplaySystemText(m_currentTarget->GetName() + L"가 공격을 시도합니다.");
		return false;
	}

	return true;
}

void BattleComp::ExecuteAttack()
{
	if (nullptr == m_currentTarget || nullptr == m_owner)
	{
		return;
	}

	if (m_bIsPlayerTurn)
	{
		m_owner->Attack(m_currentTarget);
	}
	else
	{
		m_currentTarget->Attack(m_owner);
	}
}

bool BattleComp::CheckBattleEnd()
{
	if (nullptr == m_currentTarget || nullptr == m_owner)
	{
		return true;
	}

	if (false == m_currentTarget->IsAlive())
	{
		GameInstance::GetInstance()->DisplaySystemText(m_currentTarget->GetName() + L"가 쓰러졌습니다.");
		return true;
	}

	if (false == m_owner->IsAlive())
	{
		GameInstance::GetInstance()->DisplaySystemText(m_currentTarget->GetName() + L"에게 패배했습니다.");
		return true;
	}

	return false;
}

void BattleComp::HandleBattleRewards()
{
	if (nullptr == m_currentTarget || nullptr == m_owner)
	{
		return;
	}

	Player* player = dynamic_cast<Player*>(m_owner);
	//Monster* monster = dynamic_cast<Monster*>(m_currentTarget);

	//if (player && monster && !monster->IsAlive())
	//{
	//	player->GainExperience(monster->GetDropExperience());
	//	player->GainGold(monster->GetDropGold());

	//	monster->DropLoot();
	//}

}
