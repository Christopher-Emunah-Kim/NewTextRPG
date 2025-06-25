#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/PlayerInfo.h"

constexpr __int8 LEFT_MARGIN = 4;
constexpr __int16 PLAYER_UI_BASE_Y = 10;

class Player;

class PlayerInfoUIComp : public BaseComponent
{
public:
	PlayerInfoUIComp(BaseGameObject* owner);
	virtual ~PlayerInfoUIComp() = default;


private:
	FPlayerInfo m_playerInfo;

public:

	virtual void Render(Screen* screen) override;
	
	void UpdatePlayerInfo(const FPlayerInfo& playerInfo);
};

