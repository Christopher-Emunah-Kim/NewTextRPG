#include "PlayerStatusComp.h"
#include "../../Object/Character/Player.h"

PlayerStatusComp::PlayerStatusComp(BaseGameObject* owner)
	:BaseComponent(owner), m_playerInfo(DEFAULT_LEVEL)
{
	m_playerInfo.name = owner->GetTag();
	LoadStatusByLevel();
}

bool PlayerStatusComp::GainExperience(const int32& exp)
{
	int16 levelUpCount = m_playerInfo.experience.AddExperience(exp, m_playerInfo.characterLevel);

	if (levelUpCount > 0)
	{
		m_playerInfo.characterLevel += levelUpCount;
		LoadStatusByLevel();
		return true;
	}

	return false;
}

void PlayerStatusComp::LoadStatusByLevel()
{
	FLevelProperties levelProps = FPlayerDataTablePerLevel::LoadPlayerLevelData(m_playerInfo.characterLevel);

	m_playerInfo.maxHealth = levelProps.maxHealthPerLevel;
	
	if(m_playerInfo.health > m_playerInfo.maxHealth)
	{
		m_playerInfo.health = m_playerInfo.maxHealth;
	}

	m_playerInfo.experience.SetMaxExp(levelProps.maxExperiencePerLevel);

	m_playerInfo.status = Status(
		levelProps.attackPerLevel,
		levelProps.defensePerLevel,
		levelProps.agilityPerLevel
	);
}

void PlayerStatusComp::SetPlayerInfo(const FPlayerInfo& newInfo)
{
	m_playerInfo = newInfo;
}
