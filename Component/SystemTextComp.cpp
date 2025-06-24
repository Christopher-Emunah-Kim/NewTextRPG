#include "SystemTextComp.h"
#include "../Object/BaseGameObject.h"
#include "../Screen.h"
#include "../Util/OutputSystem.h"
#include "../Util/InputSystem.h"
#include "../Core/GameInstance.h"
#include "SystemRendererComp.h"

SystemTextComp::SystemTextComp(BaseGameObject* owner)
	: BaseComponent(owner, 10)
{
}

void SystemTextComp::Render(Screen* screen)  
{  
    if (screen == nullptr)  
    {  
		return;
    }  

	vector<wstring> tempTexts;
	queue<wstring> copiedQueue = m_textQueue;

	while (false == copiedQueue.empty())
	{
		tempTexts.push_back(copiedQueue.front());
		copiedQueue.pop();
	}

	int32 outputY = DEFAULT_BASE_Y;
	int32 messageAreaWidth = SCREEN_WIDTH - GAME_PANEL_START_X - 2;
	wstring clearLine(messageAreaWidth, L' ');

	for (int32 y = DEFAULT_BASE_Y; y < DEFAULT_BASE_Y + MAX_LINES; ++y)
	{
		screen->Draw(GAME_PANEL_START_X + 1, y, clearLine);
	}

	for (size_t i = tempTexts.size(); i > 0; --i)
	{
		screen->Draw(GAME_PANEL_START_X + 1, outputY, tempTexts[i - 1]);
		outputY++;
	}
}

void SystemTextComp::Update()
{
	if (m_IsAwaitingSlections && !m_optionTexts.empty())
	{
		if (InputSystem::IsKeyPressed(EKeyCode::UP))
		{
			SelectPreviousOption();
		}
		else if (InputSystem::IsKeyPressed(EKeyCode::DOWN))
		{
			SelectNextOption();
		}
		else if (InputSystem::IsKeyPressed(EKeyCode::SPACE) || InputSystem::IsKeyPressed(EKeyCode::RETURN))
		{
			ConfirmSelection();
		}
	}

}

void SystemTextComp::SetText(const wstring& text)
{
	EnqueueText(text);
}

void SystemTextComp::EnqueueText(const wstring& text)
{
	//OutputSystem::PrintInfoMsg(L"SystemTextComp::AddText 호출됨: " + text);

	if (m_textQueue.size() >= MAX_LINES)
	{
		m_textQueue.pop();
	}

	m_textQueue.push(text);
}


void SystemTextComp::ClearTexts()
{
	queue<wstring> emptyQueue;
	m_textQueue.swap(emptyQueue);
}


void SystemTextComp::AddOption(const wstring& option, const wstring& eventName)
{
	m_optionTexts.push_back(option);
	m_optionEvents.push_back(eventName);
	m_IsAwaitingSlections = true;

	wstring optionsText = L"\n--- 선택하세요 ---\n";
	for (size_t i = 0; i < m_optionTexts.size(); ++i)
	{
		if (i == m_selectedOption)
		{
			optionsText += L"> " + m_optionTexts[i] + L" <\n";
		}
		else
		{
			optionsText += L" " + m_optionTexts[i] + L" \n";
		}
	}

	SetText(optionsText);

}

void SystemTextComp::ClearOption()
{
	m_optionTexts.clear();
	m_optionEvents.clear();
	m_selectedOption = 0;
	m_IsAwaitingSlections = false;

}

void SystemTextComp::SelectNextOption()
{
	if (m_optionTexts.empty())
	{
		return;
	}

	m_selectedOption = (m_selectedOption + 1) % m_optionTexts.size();

	wstring optionsText = L"\n--- 선택하세요 ---\n";
	for (size_t i = 0; i < m_optionTexts.size(); ++i)
	{
		if (i == m_selectedOption)
		{
			optionsText += L"> " + m_optionTexts[i] + L" <\n";
		}
		else
		{
			optionsText += L" " + m_optionTexts[i] + L" \n";
		}
	}

	SetText(optionsText);

}

void SystemTextComp::SelectPreviousOption()
{
	if (m_optionTexts.empty())
	{
		return;
	}

	m_selectedOption = (m_selectedOption + (int8)m_optionTexts.size() - 1) % m_optionTexts.size();

	wstring optionsText = L"\n--- 선택하세요 ---\n";
	for (size_t i = 0; i < m_optionTexts.size(); ++i)
	{
		if (i == m_selectedOption)
		{
			optionsText += L"> " + m_optionTexts[i] + L" <\n";
		}
		else
		{
			optionsText += L" " + m_optionTexts[i] + L" \n";
		}
	}

	SetText(optionsText);

}

void SystemTextComp::ConfirmSelection()
{
	if (m_optionTexts.empty() || m_selectedOption >= m_optionEvents.size())
	{
		return;
	}

	wstring selectedEvent = m_optionEvents[m_selectedOption];
	wstring selectionText = L"선택: " + m_optionTexts[m_selectedOption];

	SetText(selectionText);

	ClearOption();

	GetOwner()->SetCustomField(L"last_text", selectionText);

	GameInstance::GetInstance()->ProcessGameEvent(selectedEvent);

}