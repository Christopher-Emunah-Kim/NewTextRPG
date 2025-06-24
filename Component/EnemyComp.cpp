#include "EnemyComp.h"
#include "../Core/GameInstance.h"
#include "../Object/BaseGameObject.h"
#include "Player/PlayerStatusComp.h"


EnemyComp::EnemyComp(BaseGameObject* owner)
	:BaseComponent(owner, 4),
	m_health(30),
	m_maxHealth(30),
	m_status(8,3,5),
	m_dropGold(10),
	m_dropExp(15),
	m_dropItem(L"None")
{

}

void EnemyComp::Init()
{
	m_owner = GetOwner();

	if (m_owner->HasCustomField(L"health"))
	{
		m_health = stoi(m_owner->GetCustomField(L"health"));
	}

	if (m_owner->HasCustomField(L"maxHealth"))
	{
		m_maxHealth = stoi(m_owner->GetCustomField(L"maxHealth"));
	}

	if (m_owner->HasCustomField(L"attack") && m_owner->HasCustomField(L"defense") && m_owner->HasCustomField(L"agility"))
	{
		int16 atk = stoi(m_owner->GetCustomField(L"attack"));
		int16 def = stoi(m_owner->GetCustomField(L"defense"));
		int16 agi = stoi(m_owner->GetCustomField(L"agility"));
		m_status = Status(atk, def, agi);
	}

	if (m_owner->HasCustomField(L"dropExp"))
	{
		m_dropExp = stoi(m_owner->GetCustomField(L"dropExp"));
	}

	if (m_owner->HasCustomField(L"dropItem"))
	{
		m_dropItem = m_owner->GetCustomField(L"dropItem");
	}
}

void EnemyComp::LoadStateFromString(const wstring& state)
{
	m_owner->LoadStateFromString(state);
}

bool EnemyComp::TakeDamage(int32 damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		m_health = 0;
		return true;
	}
	return false;
}

void EnemyComp::ProcessDrop(BaseGameObject* player)
{
	if (nullptr == player)
	{
		return;
	}

	PlayerStatusComp* statusComp = player->GetComponentsByType<PlayerStatusComp>();
	if (statusComp)
	{
		statusComp->GainExperience(m_dropExp);
		statusComp->GainPlayerGold(statusComp->GetPlayerGold());

		GameInstance::GetInstance()->DisplaySystemText(L"경험치 " + to_wstring(m_dropExp) + L"와 골드 " +
			to_wstring(m_dropGold) + L"를 획득했습니다.");

		if (m_dropItem != L"None")
		{
			GameInstance::GetInstance()->DisplaySystemText(L"아이템 " + m_dropItem + L"을(를) 획득했습니다.");
		}
	}
}
