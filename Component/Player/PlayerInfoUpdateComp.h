#pragma once
#include "../BaseComponent.h"

class PlayerInfoRenderComp;
class BaseGameObject;

class PlayerInfoUpdateComp : public BaseComponent
{
public:
	PlayerInfoUpdateComp(BaseGameObject* owner);
	virtual ~PlayerInfoUpdateComp() = default;

private:
	PlayerInfoRenderComp* m_renderComp = nullptr;
	BaseGameObject* m_player = nullptr;

public:
	virtual void Init() override;
	virtual void Update() override;

	void UpdatePlayerInfo();
	void SetTargetPlayer(BaseGameObject* player);
};

