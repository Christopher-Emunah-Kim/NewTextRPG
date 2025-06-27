#pragma once
#include "BaseCharacter.h"
#include "../../Util/Type/CharacterInfo.h"

constexpr __int32 DEFAULT_DAMAGE = 3;

class BattleCharacter  abstract : public BaseCharacter
{
public:
	BattleCharacter(BaseLevel* level, const wstring& tag);
	virtual ~BattleCharacter();

protected:
	FBattleCharacterInfo m_battleCharacterInfo;

public:
	virtual void Init() override;
	virtual void Interact(BaseCharacter* other) override;

	virtual void Attack(BattleCharacter* target);
	virtual void TakeDamage(const int32& damage);
	virtual bool IsAlive() const;

	int32 CalculateDamage(BattleCharacter* target) const;

	void SetHealth(const int32& health);
	void SetMaxHealth(const int32& maxHealth);
	void SetStatus(const Status& status);

	int32 GetHealth() const noexcept { return m_battleCharacterInfo.health; }
	int32 GetMaxHealth() const noexcept { return m_battleCharacterInfo.maxHealth; }
	const Status& GetStatus() const noexcept { return m_battleCharacterInfo.status; }
	const FBattleCharacterInfo& GetBattleCharacterInfo() const noexcept { return m_battleCharacterInfo; }
};

