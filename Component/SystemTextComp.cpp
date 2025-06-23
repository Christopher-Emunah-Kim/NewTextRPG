#include "SystemTextComp.h"
#include "../Object/BaseGameObject.h"
#include "../Screen.h"
#include "../Util/OutputSystem.h"

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
