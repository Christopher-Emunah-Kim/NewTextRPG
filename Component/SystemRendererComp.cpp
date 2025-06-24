#include "SystemRendererComp.h"
#include "../Object/BaseGameObject.h"
#include "../Screen.h"


SystemRendererComp::SystemRendererComp(BaseGameObject* owner)
	: BaseComponent(owner)
{
}

void SystemRendererComp::Render(Screen* screen)
{
}

void SystemRendererComp::Update()
{

}

void SystemRendererComp::SetText(const wstring& text)
{

}

void SystemRendererComp::EnqueueText(const wstring& text)
{

}

void SystemRendererComp::ClearTexts()
{

}

void SystemRendererComp::AddOption(const wstring& option, const wstring& eventName)
{
}

void SystemRendererComp::ClearOption()
{
}

void SystemRendererComp::SelectNextOption()
{
}

void SystemRendererComp::SelectPreviousOption()
{
}

void SystemRendererComp::ConfirmSelection()
{
}
