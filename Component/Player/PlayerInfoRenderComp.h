#pragma once
#include "../BaseComponent.h"

class Player;

class PlayerInfoRenderComp : public BaseComponent
{
public:
	PlayerInfoRenderComp(BaseGameObject* owner);
	virtual ~PlayerInfoRenderComp() = default;


private:
	wstring m_playerName;
	int16 m_level;
	int16 m_attack;
	int16 m_defense;
	int16 m_agility;
	int32 m_health;
	int32 m_maxHealth;
	int32 m_experience;
	int32 m_maxExperience;
	int32 m_gold;

public:

	virtual void Render(Screen* screen) override;
	
	void UpdateStatus(const wstring& name, int16 level, int32 health, int32 maxHealth,
		int32 exp, int32 maxExp, int16 attack, int16 defense,
		int16 agility, int32 gold);
};

