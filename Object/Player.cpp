#include "Player.h"
#include "../Screen.h"
#include "../Component/ControllerComp.h"
#include "../Component/RendererComp.h"



void Player::Init()
{
	SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	AddComponent(new ControllerComp(this));
	AddComponent(new RendererComp(this, "@"));

	BaseGameObject::Init();
}