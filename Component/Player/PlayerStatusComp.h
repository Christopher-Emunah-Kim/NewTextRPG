#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/CharacterInfo.h"


class PlayerStatusComp final : public BaseComponent
{
public:
	PlayerStatusComp(BaseGameObject* owner);
	virtual ~PlayerStatusComp() = default;

	void LoadStatusByLevel();
	Status GetTotalStatus() const;

	void SetPlayerInfo(const FPlayerInfo& newInfo);
	bool GainExperience(int32 exp);
	bool RecoverHealth(int32 amount);
	bool TakeDamage(int32 amount);

	inline const FPlayerInfo& GetPlayerInfo() const noexcept { return m_playerInfo; }

private:
	FPlayerInfo m_playerInfo;
};

