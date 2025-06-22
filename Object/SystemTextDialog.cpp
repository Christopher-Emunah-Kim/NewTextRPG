#include "SystemTextDialog.h"
#include "../Component/SystemTextComp.h"

SystemTextDialog::SystemTextDialog(BaseLevel* level)
	: BaseGameObject(level, L"SystemTextDialog")
{ }


void SystemTextDialog::Init()
{
	SetPosition(0, SCREEN_HEIGHT / 2);

	if (false == HasComponentType<SystemTextComp>())
	{
		AddComponent(new SystemTextComp(this));
	}

	BaseGameObject::Init();
	
	SetSystemText(L"===예시 시스템 메시지가 여기에 표시됩니다.");
}

void SystemTextDialog::SetSystemText(const wstring& text) noexcept
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
