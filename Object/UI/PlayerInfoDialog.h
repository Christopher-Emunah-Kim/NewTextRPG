#pragma once
#include "../BaseGameObject.h"

class Player;
class BaseLevel;
class PlayerInfoUIComp;

class PlayerInfoDialog final : public BaseGameObject
{
public:
	PlayerInfoDialog(BaseLevel* level);
	virtual ~PlayerInfoDialog() = default;

private:
	PlayerInfoUIComp* m_renderComp = nullptr;

public:

	virtual void Init() override;

	void UpdatePlayerInfoDialog(const Player& player);
	void RegisterPlayerInfoDialogInNewLevel(BaseLevel* newLevel);

};

