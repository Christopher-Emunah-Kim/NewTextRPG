#pragma once
#include "../BaseGameObject.h"

class Player;
class BaseLevel;
class PlayerInfoRenderComp;

class PlayerInfoDialog final : public BaseGameObject
{
public:
	PlayerInfoDialog(BaseLevel* level);
	virtual ~PlayerInfoDialog() = default;

private:
	PlayerInfoRenderComp* m_renderComp = nullptr;

public:

	virtual void Init() override;

	void UpdatePlayerInfoDialog(const Player& player);
	void RegisterPlayerInfoDialogInNewLevel(BaseLevel* newLevel);

};

