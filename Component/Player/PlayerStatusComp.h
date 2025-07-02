#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/CharacterInfo.h"


class PlayerStatusComp final : public BaseComponent
{
public:
	PlayerStatusComp(BaseGameObject* owner);
	virtual ~PlayerStatusComp() = default;

private:
	FPlayerInfo m_playerInfo;

public:
	void LoadStatusByLevel();
	Status GetTotalStatus() const;

	void SetPlayerInfo(const FPlayerInfo& newInfo);
	bool GainExperience(const int32& exp);
	bool UseGold(int16 amount);
	void GainGold(int16 amount);
	bool RecoverHealth(int32 amount);
	bool TakeDamage(int32 amount);

	inline const FPlayerInfo& GetPlayerInfo() const noexcept { return m_playerInfo; }
};

