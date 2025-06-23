#pragma once
#include "../BaseGameObject.h"

class Player;
class BaseLevel;
class PlayerInfoComp;

class PlayerInfoDialog : public BaseGameObject
{
public:
	PlayerInfoDialog(BaseLevel* level);
	virtual ~PlayerInfoDialog() = default;

private:

public:

	virtual void Init() override;

	void UpdatePlayerInfoDialog(const Player& player);
	void RegisterPlayerInfoDialogInNewLevel(BaseLevel* newLevel);

};

