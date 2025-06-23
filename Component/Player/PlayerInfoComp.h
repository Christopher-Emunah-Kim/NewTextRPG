#pragma once
#include "../BaseComponent.h"

class Player;

class PlayerStatusComp : public BaseComponent
{
public:
	PlayerStatusComp(BaseGameObject* owner);
	virtual ~PlayerStatusComp() = default;

	virtual void Render(Screen* screen) override;
	
	void UpdateStatus(const Player& player);
};

