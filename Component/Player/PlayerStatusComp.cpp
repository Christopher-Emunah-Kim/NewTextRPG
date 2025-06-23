#include "PlayerStatusComp.h"
#include "../../Object/Player.h"

PlayerStatusComp::PlayerStatusComp(BaseGameObject* owner)
	:BaseComponent(owner),
	m_playerName(owner->GetTag()),
	m_level(1),
	m_health(DEFAULT_CHARACTER_MAX_HEALTH),
	m_maxHealth(DEFAULT_CHARACTER_MAX_HEALTH),
	m_experience(0),
	m_maxExperience(DEFAULT_PLAYER_MAX_EXPERIENCE),
	m_gold(0),
	m_status(Status(DEFAULT_ATTACK, DEFAULT_DEFENSE, DEFAULT_AGILITY))
{
	LoadStatusByLevel();
}

bool PlayerStatusComp::GainExperience(const int32& exp)
{
	m_experience += exp;

	return CheckLevelUp();
}

bool PlayerStatusComp::CheckLevelUp()
{
	bool bIsLeveledUp = false;

	while (m_experience >= m_maxExperience)
	{
		m_level++;
		m_experience -= m_maxExperience;
		bIsLeveledUp = true;
		LoadStatusByLevel();
	}

	return bIsLeveledUp;
}

void PlayerStatusComp::LoadStatusByLevel()
{
	PlayerDataTablePerLevel dataTable;

	FLevelProperties levelProps = dataTable.LoadLevelData(m_level);

	m_maxExperience = levelProps.maxExperiencePerLevel;
	m_maxHealth = levelProps.maxHealthPerLevel;

	m_status = Status(
		levelProps.attackPerLevel,
		levelProps.defensePerLevel,
		levelProps.agilityPerLevel
	);
}

void PlayerStatusComp::SetStatus(const Status& status)
{
	m_status = status;
}

void PlayerStatusComp::SetPlayerLevel(const int16& level)
{
	m_level = level;

	if (m_level < 1)
	{
		m_level = 1;
	}
	if (m_level > 100)
	{
		m_level = 100;
	}

	LoadStatusByLevel();
}

void PlayerStatusComp::SetPlayerHealth(const int32& health)
{
	m_health = health;
	if (m_health < 0)
	{
		m_health = 0;
	}
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}

void PlayerStatusComp::SetPlayerMaxHealth(const int32& maxHealth)
{
	m_maxHealth = maxHealth;

	if (m_maxHealth < 1)
	{
		m_maxHealth = 1;
	}
}

void PlayerStatusComp::SetPlayerExperience(const int32& exp)
{
	m_experience = exp;

	if (m_experience < 0)
	{
		m_experience = 0;
	}

	CheckLevelUp();
}

void PlayerStatusComp::SetPlayerMaxExperience(const int32& maxExp)
{
	m_maxExperience = maxExp;

	if (m_maxExperience < 1)
	{
		m_maxExperience = 1;
	}
}

void PlayerStatusComp::SetPlayerGold(const int32& gold)
{
	m_gold = gold;

	if (m_gold < 0)
	{
		m_gold = 0;
	}
}

void PlayerStatusComp::SetPlayerName(const wstring& name)
{
	m_playerName = name;
}
