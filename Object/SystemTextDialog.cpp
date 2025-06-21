#include "SystemTextDialog.h"
#include "../Component/SystemTextComp.h"

SystemTextDialog::SystemTextDialog(BaseLevel* level)
	: BaseGameObject(level, "SystemTextDialog")
{ }


void SystemTextDialog::Init()
{
	SetPosition(0, SCREEN_HEIGHT - 2);

	if (IsComponentsEmpty())
	{
		AddComponent(new SystemTextComp(this));
	}

	BaseGameObject::Init();
}

void SystemTextDialog::SetSystemText(const string& text) noexcept
{
	SystemTextComp* textComp = nullptr;

	vector<BaseComponent*> components = GetComponents();

	for (size_t i = 0; i < components.size(); ++i)
	{
		textComp = dynamic_cast<SystemTextComp*>(components[i]);
		if (textComp)
		{
			textComp->SetText(text);
			break;
		}
	}
}
