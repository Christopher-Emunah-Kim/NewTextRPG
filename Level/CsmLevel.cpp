#include "CsmLevel.h"
#include "../Core/GameInstance.h"
#include "../Util/InputSystem.h"


void CsmLevel::Init()
{
	Welcome();
}

void CsmLevel::Render(Screen* screen)
{	
	for (int line = 0; line < _texts.size(); ++line)
	{
		screen->Draw(0, line, _texts[line]);
	}
	screen->Draw(0, 10, L"입력 : " + InputSystem::GetBuffer());
}

void CsmLevel::Welcome()
{
	AddText(L"1. 마을로 가기");
	AddText(L"2. 던전으로 가기");
	AddText(L"3. 되돌아가기");

	InputSystem::BindAction(
		{
			{L"1", bind(&CsmLevel::EnterVillage, this)},
			{L"2", bind(&CsmLevel::EnterDungeon, this)},
			{L"3", bind(&CsmLevel::GoToHell, this)}
		}
	);

	// 하나씩 할 수도 있고, 위처럼 여러 개 할 수도 있고..
	// InputSystem::BindAction(L"1", bind(&CsmLevel::EnterVillage, this));
	// InputSystem::BindAction(L"2", bind(&CsmLevel::EnterDungeon, this));
	// InputSystem::BindAction(L"3", bind(&CsmLevel::GoToHell, this));

	InputSystem::BindActionOnInputError(
		[this]()
		{
			ClearText();
			AddText(L"잘못된 입력입니다. 다시 시도하세요.");
			Welcome();
		}
	);
}

void CsmLevel::EnterVillage()
{
	ClearText();

	AddText(L"마을로 돌아가기는 개뿔 다시 처음부터입니다.");
	
	InputSystem::Clear();
	Welcome();
}

void CsmLevel::EnterDungeon()
{
	ClearText();
	
	AddText(L"던전으로 이동하기는 개뿔 다시 처음부터입니다.");

	InputSystem::Clear();
	Welcome();
}

void CsmLevel::GoToHell()
{
	ClearText();
	
	AddText(L"무한 지옥에 오신 것을 환영합니다.");

	InputSystem::Clear();
	Welcome();
}

void CsmLevel::AddText(wstring text)
{
	_texts.push_back(text);
}

void CsmLevel::ClearText()
{
	_texts.clear();
}
