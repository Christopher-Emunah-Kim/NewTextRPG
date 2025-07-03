#pragma once
#include "BaseCharacter.h"
#include "../../Util/Type/CharacterInfo.h"

constexpr __int32 DEFAULT_DAMAGE = 3;

class BattleCharacter abstract : public BaseCharacter
{
public:
	BattleCharacter(BaseLevel* level, const wstring& tag);
	virtual ~BattleCharacter();

private:
	int32 CalculateDamage(BattleCharacter* target) const;

public:
	virtual void Init() override;
	virtual void Interact(BaseCharacter* other) override;

	virtual void Attack(BattleCharacter* target);
	virtual void TakeDamage(int32 damage);
	virtual bool IsAlive() const;

	const FBattleCharacterInfo& GetBattleCharacterInfo() const noexcept { return m_battleCharacterInfo; }

protected:
	FBattleCharacterInfo m_battleCharacterInfo;

};

