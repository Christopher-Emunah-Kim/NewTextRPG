#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/PlayerInfo.h"

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

