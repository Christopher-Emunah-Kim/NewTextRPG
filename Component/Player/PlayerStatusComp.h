#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/PlayerInfo.h"


class PlayerStatusComp final : public BaseComponent
{
public:
	PlayerStatusComp(BaseGameObject* owner);
	virtual ~PlayerStatusComp() = default;

private:
	FPlayerInfo m_playerInfo;

public:
	bool GainExperience(const int32& exp);

	void LoadStatusByLevel();

	void SetPlayerInfo(const FPlayerInfo& newInfo);

	inline const FPlayerInfo& GetPlayerInfo() const noexcept { return m_playerInfo; }
};

