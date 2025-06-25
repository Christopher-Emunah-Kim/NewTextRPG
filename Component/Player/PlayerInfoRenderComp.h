#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/PlayerInfo.h"

class Player;

class PlayerInfoRenderComp : public BaseComponent
{
public:
	PlayerInfoRenderComp(BaseGameObject* owner);
	virtual ~PlayerInfoRenderComp() = default;


private:
	FPlayerInfo m_playerInfo;

public:

	virtual void Render(Screen* screen) override;
	
	void UpdatePlayerInfo(const FPlayerInfo& playerInfo);
};

