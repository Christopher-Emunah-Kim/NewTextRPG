#pragma once
#include "BattleCharacter.h"


class Monster final : public BattleCharacter
{
public:
	Monster(BaseLevel* level, const wstring& tag); 
	Monster(BaseLevel* level, const wstring& tag, const FMonsterInfo& info);

	virtual ~Monster();

private:
	FMonsterInfo m_monsterInfo;

public:
	virtual void Init() override;

	void DropRewards();



	inline void SetDropGoldAmount(const int16& amount) { m_monsterInfo.dropGold = amount; }
	inline void SetDropExperienceAmount(const int16& amount) { m_monsterInfo.dropExperience = amount; }
	inline void SetDropItemId(const int32& id) { m_monsterInfo.dropItemId = id; }

	inline int16 GetDropGold() const noexcept { return  m_monsterInfo.dropGold; }
	inline int16 GetDropExperience() const noexcept { return m_monsterInfo.dropExperience; }
	inline int32 GetDropItemId() const { return m_monsterInfo.dropItemId; }
	inline const FMonsterInfo& GetMonsterInfo() const { return m_monsterInfo; }
};

