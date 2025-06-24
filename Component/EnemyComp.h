#pragma once
#include "BaseComponent.h"

class BaseGameObject;

class EnemyComp : public BaseComponent
{
public:
	EnemyComp(BaseGameObject* owner);
	virtual ~EnemyComp() = default;

private:
	int32 m_health;
	int32 m_maxHealth;
	Status m_status;
	int32 m_dropGold;
	int32 m_dropExp;
	wstring m_dropItem;

public:
	virtual void Init() override;
	
	void LoadStateFromString(const wstring& state);

	bool TakeDamage(int32 damage);
	void ProcessDrop(BaseGameObject* player);


	inline void SetHealth(const int32& health) { m_health = health; }
	inline void SetMaxHealth(const int32& maxHealth) { m_maxHealth = maxHealth; }

};

