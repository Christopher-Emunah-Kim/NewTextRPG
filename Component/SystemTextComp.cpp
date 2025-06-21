#include "SystemTextComp.h"
#include "../Object/BaseGameObject.h"
#include "../Screen.h"

SystemTextComp::SystemTextComp(BaseGameObject* owner)
	: BaseComponent(owner, 3), m_systemText(" ")
{
}

void SystemTextComp::Render(Screen* screen)
{
	if (screen && !m_systemText.empty())
	{
		screen->Draw(0, SCREEN_HEIGHT - 2, m_systemText);
	}
}

void SystemTextComp::SetText(const string& text)
{
	m_systemText = text;
}
