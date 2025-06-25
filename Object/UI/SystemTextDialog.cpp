#include "SystemTextDialog.h"
#include "../../Component/UI/SystemTextUIComp.h"
#include "../../Level/BaseLevel.h"

SystemTextDialog::SystemTextDialog(BaseLevel* level)
	: BaseGameObject(level, L"SystemTextDialog")
{
}


void SystemTextDialog::Init()
{

	SetPosition(0, SCREEN_HEIGHT / 2);

	if (false == HasComponentType<SystemTextUIComp>())
	{
		AddComponent(new SystemTextUIComp(this));
	}

	BaseGameObject::Init();
	
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 0.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 1.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 2.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 3.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 4.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 5.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 6.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 7.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 8.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 9.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 10.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 11.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 12.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 13.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 14.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 15.");
	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 16.");
}

void SystemTextDialog::SetSystemText(const wstring& text) 
{
	SystemTextUIComp* textComp = nullptr;

	vector<BaseComponent*> components = GetComponents();

	for (size_t i = 0; i < components.size(); ++i)
	{
		textComp = dynamic_cast<SystemTextUIComp*>(components[i]);
		if (textComp)
		{
			textComp->SetText(text);
			break;
		}
	}
}

void SystemTextDialog::ClearSystemText()
{
	SystemTextUIComp* textComp = nullptr;

	vector<BaseComponent*> components = GetComponents();

	for (size_t i = 0; i < components.size(); ++i)
	{
		textComp = dynamic_cast<SystemTextUIComp*>(components[i]);
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
