#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/StatusType.h"
#include "../../Util/Type/LootType.h"


class PlayerStatusComp : public BaseComponent
{
public:
	PlayerStatusComp(BaseGameObject* owner);
	virtual ~PlayerStatusComp() = default;

private:
	Status		m_status;
	wstring		m_playerName;
	int16		m_level;
	int32		m_health;
	int32		m_maxHealth;
	int32		m_experience;
	int32		m_maxExperience;
	int32		m_gold;

public:
	bool GainExperience(const int32& exp);
	bool CheckLevelUp();
	void LoadStatusByLevel();

	void SetStatus(const Status& status);
	void SetPlayerLevel(const int16& level);
	void SetPlayerHealth(const int32& health);
	void SetPlayerMaxHealth(const int32& maxHealth);
	void SetPlayerExperience(const int32& exp);
	void SetPlayerMaxExperience(const int32& maxExp);
	void SetPlayerGold(const int32& gold);
	void SetPlayerName(const wstring& name);

	const Status& GetStatus() const { return m_status; }
	const int16& GetPlayerLevel() const { return m_level; }
	const int32& GetPlayerHealth() const { return m_health; }
	const int32& GetPlayerMaxHealth() const { return m_maxHealth; }
	const int32& GetPlayerExperience() const { return m_experience; }
	const int32& GetPlayerMaxExperience() const { return m_maxExperience; }
	const int32& GetPlayerGold() const { return m_gold; }
	const wstring& GetPlayerName() const { return m_playerName; }
};

