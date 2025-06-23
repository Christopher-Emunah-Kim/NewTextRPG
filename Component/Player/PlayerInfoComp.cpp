#include "PlayerInfoComp.h"
#include "../../../NewTextRPG/Screen.h"

PlayerInfoComp::PlayerInfoComp(BaseGameObject* owner)
	:BaseComponent(owner, 3)
{

}

void PlayerInfoComp::Render(Screen* screen)
{
	if (screen == nullptr)
		return;

	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		screen->Draw(PLAYERINFO_PANEL_WIDTH, y, L'|');
	}


}

void PlayerInfoComp::UpdateStatus(const Player& player)
{
}
