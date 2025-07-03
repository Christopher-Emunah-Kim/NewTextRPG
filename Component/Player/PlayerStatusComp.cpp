#include "PlayerStatusComp.h"
#include "EquipmentComp.h"
#include "../../Core/GameInstance.h"
#include "../../Object/Character/Player.h"

PlayerStatusComp::PlayerStatusComp(BaseGameObject* owner)
	:BaseComponent(owner), m_playerInfo(DEFAULT_LEVEL)
{
	LoadStatusByLevel();
	m_playerInfo.name = owner->GetTag();
}

void PlayerStatusComp::LoadStatusByLevel()
{
	FLevelProperties levelProps = FPlayerDataTablePerLevel::LoadPlayerLevelData(m_playerInfo.characterLevel);


	m_playerInfo.maxHealth = levelProps.maxHealthPerLevel;

	if (m_playerInfo.health > m_playerInfo.maxHealth || m_playerInfo.health <= 0)
	{
		m_playerInfo.health = m_playerInfo.maxHealth;
	}

	m_playerInfo.experience.SetMaxExp(levelProps.maxExperiencePerLevel);

	m_playerInfo.status = Status(
		levelProps.attackPerLevel,
		levelProps.defensePerLevel,
		levelProps.agilityPerLevel
	);

	GameInstance::GetInstance()->UpdatePlayerHealth(m_playerInfo.health, m_playerInfo.maxHealth);
	GameInstance::GetInstance()->UpdatePlayerStatus(GetTotalStatus());
}

Status PlayerStatusComp::GetTotalStatus() const 
{
	Status baseStatus = m_playerInfo.status;

	EquipmentComp* equipComp = m_owner->GetComponentByType<EquipmentComp>();
	if (equipComp)
	{
		Status equipStatus = equipComp->GetTotalEquipmentStatus();
		baseStatus = Status::AddStatus(baseStatus, equipStatus);
	}

	return baseStatus;

}

bool PlayerStatusComp::GainExperience(int32 exp)
{
	int16 levelUpCount = m_playerInfo.experience.AddExperience(exp, m_playerInfo.characterLevel);

	GameInstance::GetInstance()->UpdatePlayerExperience(m_playerInfo.experience);

	if (levelUpCount > 0)
	{
		m_playerInfo.characterLevel += levelUpCount;
		LoadStatusByLevel();

		GameInstance::GetInstance()->UpdatePlayerLevel(m_playerInfo.characterLevel);
		GameInstance::GetInstance()->UpdatePlayerStatus(GetTotalStatus());

		return true;
	}

	return false;
}

bool PlayerStatusComp::UseGold(int16 amount)
{
	bool result =  m_playerInfo.gold.UseGold(amount);

	if (result)
	{
		GameInstance::GetInstance()->UpdatePlayerGold(m_playerInfo.gold);
	}

	return result;
}

void PlayerStatusComp::GainGold(int16 amount)
{
	m_playerInfo.gold.GainGold(amount);

	GameInstance::GetInstance()->UpdatePlayerGold(m_playerInfo.gold);
	
}

bool PlayerStatusComp::RecoverHealth(int32 amount)
{
	if (m_playerInfo.health >= m_playerInfo.maxHealth)
	{
		return false;
	}

	m_playerInfo.health += amount;

	if (m_playerInfo.health > m_playerInfo.maxHealth)
	{
		m_playerInfo.health = m_playerInfo.maxHealth;
	}

	GameInstance::GetInstance()->UpdatePlayerHealth(m_playerInfo.health, m_playerInfo.maxHealth);
	return true;
}

bool PlayerStatusComp::TakeDamage(int32 amount)
{
	if (amount <= 0)
	{
		return false;
	}

	m_playerInfo.health -= amount;

	if (m_playerInfo.health < 0)
	{
		m_playerInfo.health = 0;
	}

	GameInstance::GetInstance()->UpdatePlayerHealth(m_playerInfo.health, m_playerInfo.maxHealth);
	return m_playerInfo.health > 0;
}


void PlayerStatusComp::SetPlayerInfo(const FPlayerInfo& newInfo)
{
	m_playerInfo = newInfo;

	GameInstance* gameInstance = GameInstance::GetInstance();
	gameInstance->UpdatePlayerName(m_playerInfo.name);
	gameInstance->UpdatePlayerLevel(m_playerInfo.characterLevel);
	gameInstance->UpdatePlayerHealth(m_playerInfo.health, m_playerInfo.maxHealth);
	gameInstance->UpdatePlayerStatus(GetTotalStatus());
	gameInstance->UpdatePlayerExperience(m_playerInfo.experience);
	gameInstance->UpdatePlayerGold(m_playerInfo.gold);
}
