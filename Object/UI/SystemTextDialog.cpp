#include "SystemTextDialog.h"
#include "../../Component/UI/SystemUIComp.h"
#include "../../Level/BaseLevel.h"

SystemTextDialog::SystemTextDialog(BaseLevel* level)
	: BaseGameObject(level, L"SystemTextDialog")
{
}


void SystemTextDialog::Init()
{

	SetPosition(0, SCREEN_HEIGHT);

	if (false == HasComponentType<SystemUIComp>())
	{
		AddComponent(new SystemUIComp(this));
	}

	BaseGameObject::Init();
	
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 0.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 1.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 2.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 3.");
}

void SystemTextDialog::SetSystemText(const wstring& text) 
{
	SystemUIComp* textComp = nullptr;

	vector<BaseComponent*> components = GetComponents();

	for (size_t i = 0; i < components.size(); ++i)
	{
		textComp = dynamic_cast<SystemUIComp*>(components[i]);
		if (textComp)
		{
			textComp->SetText(text);
			break;
		}
	}
}

void SystemTextDialog::ClearSystemText()
{
	SystemUIComp* textComp = nullptr;

	vector<BaseComponent*> components = GetComponents();

	for (size_t i = 0; i < components.size(); ++i)
	{
		textComp = dynamic_cast<SystemUIComp*>(components[i]);
		if (textComp)
		{
			textComp->ClearTexts();
			break;
		}
	}
}

void SystemTextDialog::RegisterSystemTextInNewLevel(BaseLevel* newLevel)
{
	if (GetLevel() != newLevel)
	{
		if (GetLevel())
		{
			GetLevel()->DetachObject(this);
		}

		SetLevel(newLevel);

		if (newLevel)
		{
			newLevel->AddObject(this);
		}
	}
}
