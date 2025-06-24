//#include "SystemTextDialog.h"
//#include "../../Core/GameInstance.h"
//#include "../../Component/SystemTextComp.h"
//#include "../../Level/BaseLevel.h"
//#include "../../Util/InputSystem.h"
//
//SystemTextDialog::SystemTextDialog(BaseLevel* level)
//	: BaseGameObject(level, L"SystemTextDialog", L"SystemText")
//{ }
//
//
//void SystemTextDialog::Init()
//{
//	//SetPosition(0, SCREEN_HEIGHT / 2);
//
//	if (false == HasComponentType<SystemTextComp>())
//	{
//		AddComponent(new SystemTextComp(this));
//	}
//
//	BaseGameObject::Init();
//	
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 0.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 1.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 2.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 3.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 4.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 5.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 6.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 7.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 8.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 9.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 10.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 11.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 12.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 13.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 14.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 15.");
//// 	SetSystemText(L"=== 예시로 시스템 메시지가 여기에 표시됩니다 16.");
//}
//
//void SystemTextDialog::Update()
//{
//	if (m_awaitingSelection && !m_optionTexts.empty())
//	{
//		if (InputSystem::IsKeyPressed(EKeyCode::UP))
//		{
//			SelectPreviousOption();
//		}
//		else if (InputSystem::IsKeyPressed(EKeyCode::DOWN))
//		{
//			SelectNextOption();
//		}
//		else if (InputSystem::IsKeyPressed(EKeyCode::SPACE) || InputSystem::IsKeyPressed(EKeyCode::RETURN))
//		{
//			ConfirmSelection();
//		}
//	}
//
//	BaseGameObject::Update();
//}
//
//void SystemTextDialog::SetSystemText(const wstring& text) 
//{
//	SystemTextComp* textComp = GetComponentsByType<SystemTextComp>();
//
//	if (textComp)
//	{
//		textComp->SetText(text);
//
//		SetCustomField(L"last_text", text);
//	}
//
//// 	SystemTextComp* textComp = nullptr;
//// 
//// 	vector<BaseComponent*> components = GetComponents();
//// 
//// 	for (size_t i = 0; i < components.size(); ++i)
//// 	{
//// 		textComp = dynamic_cast<SystemTextComp*>(components[i]);
//// 		if (textComp)
//// 		{
//// 			textComp->SetText(text);
//// 			break;
//// 		}
//// 	}
//}
//
//void SystemTextDialog::ClearSystemText()
//{
//	SystemTextComp* textComp = GetComponentsByType<SystemTextComp>();
//	if (textComp)
//	{
//		textComp->ClearTexts();
//	}
//
//// 	SystemTextComp* textComp = nullptr;
//// 
//// 	vector<BaseComponent*> components = GetComponents();
//// 
//// 	for (size_t i = 0; i < components.size(); ++i)
//// 	{
//// 		textComp = dynamic_cast<SystemTextComp*>(components[i]);
//// 		if (textComp)
//// 		{
//// 			textComp->ClearTexts();
//// 			break;
//// 		}
//// 	}
//}
//
//void SystemTextDialog::AddOption(const wstring& option, const wstring& eventName)
//{
//	m_optionTexts.push_back(option);
//	m_optionEvents.push_back(eventName);
//	m_awaitingSelection = true;
//
//	SystemTextComp* textComp = GetComponentsByType<SystemTextComp>();
//	if (textComp)
//	{
//		wstring optionsText = L"\n--- 선택하세요 ---\n";
//		for (size_t i = 0; i < m_optionTexts.size(); ++i)
//		{
//			if (i == m_selectedOption)
//			{
//				optionsText += L"> " + m_optionTexts[i] + L" <\n";
//			}
//			else
//			{
//				optionsText += L" " + m_optionTexts[i] + L" \n";
//			}
//		}
//
//		textComp->SetText(optionsText);
//	}
//}
//
//void SystemTextDialog::ClearOptions()
//{
//	m_optionTexts.clear();
//	m_optionEvents.clear();
//	m_selectedOption = 0;
//	m_awaitingSelection = false;
//}
//
//void SystemTextDialog::SelectNextOption()
//{
//	if (m_optionTexts.empty())
//	{
//		return;
//	}
//
//	m_selectedOption = (m_selectedOption + 1) % m_optionTexts.size();
//
//	SystemTextComp* textComp = GetComponentsByType<SystemTextComp>();
//	if (textComp)
//	{
//		wstring optionsText = L"\n--- 선택하세요 ---\n";
//		for (size_t i = 0; i < m_optionTexts.size(); ++i)
//		{
//			if (i == m_selectedOption)
//			{
//				optionsText += L"> " + m_optionTexts[i] + L" <\n";
//			}
//			else
//			{
//				optionsText += L" " + m_optionTexts[i] + L" \n";
//			}
//		}
//
//		textComp->SetText(optionsText);
//	}
//}
//
//void SystemTextDialog::SelectPreviousOption()
//{
//	if (m_optionTexts.empty())
//	{
//		return;
//	}
//
//	m_selectedOption = (m_selectedOption + m_optionTexts.size() - 1 ) % m_optionTexts.size();
//
//	SystemTextComp* textComp = GetComponentsByType<SystemTextComp>();
//	if (textComp)
//	{
//		wstring optionsText = L"\n--- 선택하세요 ---\n";
//		for (size_t i = 0; i < m_optionTexts.size(); ++i)
//		{
//			if (i == m_selectedOption)
//			{
//				optionsText += L"> " + m_optionTexts[i] + L" <\n";
//			}
//			else
//			{
//				optionsText += L" " + m_optionTexts[i] + L" \n";
//			}
//		}
//
//		textComp->SetText(optionsText);
//	}
//}
//
//void SystemTextDialog::ConfirmSelection()
//{
//	if (m_optionTexts.empty() || m_selectedOption >= m_optionEvents.size())
//	{
//		return;
//	}
//
//	wstring selectedEvent = m_optionEvents[m_selectedOption];
//
//	wstring selectionText = L"선택: " + m_optionTexts[m_selectedOption];
//	SetSystemText(selectionText);
//
//	ClearOptions();
//
//	GameInstance::GetInstance()->ProcessGameEvent(selectedEvent);
//}
//
////void SystemTextDialog::RegisterSystemTextInNewLevel(BaseLevel* newLevel)
////{
////	if (GetLevel() != newLevel)
////	{
////		if (GetLevel())
////		{
////			GetLevel()->DetachObject(this);
////		}
////
////		SetLevel(newLevel);
////
////		if (newLevel)
////		{
////			newLevel->AddObject(this);
////		}
////	}
////}
