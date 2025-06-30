#include "DungeonLevel.h"
#include "../Core/GameInstance.h"
#include "../Object/UI/HUDUI.h"
#include "../Screen.h"
#include "../Util/InputSystem.h"
#include "../Manager/LevelManager.h"


void DungeonLevel::Init()
{
	SetHUDUI();

	Welcome();

	BaseLevel::Init();
}

void DungeonLevel::Render(Screen* screen)
{
	m_HUDUI->ClearSystemText();

	for (size_t line = 0; line < m_systemTexts.size(); ++line)
	{
		m_HUDUI->EnqueueText(m_systemTexts[line]);
	}

	BaseLevel::Render(screen);
}

void DungeonLevel::Release()
{
	delete m_HUDUI;
	m_HUDUI = nullptr;
	GameInstance::GetInstance()->SetHUDUI(nullptr);
}

void DungeonLevel::SetHUDUI()
{
	GameInstance* gameInstance = GameInstance::GetInstance();

	m_HUDUI = new HUDUI(this);
	m_HUDUI->Init();
	gameInstance->SetHUDUI(m_HUDUI);
}

void DungeonLevel::Welcome()
{
	ClearText();

	AddText(L"============================================");
	AddText(L"당신은 동굴 입구 앞에 섰습니다.");
	AddText(L"으스스한 동굴이 당신을 반깁니다..");
	AddText(L"도전하시겠습니까?");
	AddText(L"");
	AddText(L"[던전 메뉴 옵션]");
	AddText(L"1. 인생은 모험이지! 도전한다.");
	AddText(L"2. 지금은 아닌것 같아.. 마을로 돌아갈래");
	AddText(L"");
	AddText(L"============================================");
	AddText(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&DungeonLevel::EnterStage, this)},
			{L"2", bind(&DungeonLevel::BackToVillage, this)},
		}
	);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			ClearText();
			AddText(L"잘못된 입력입니다. 다시 시도하세요.");
			Welcome();
		}
	);
}

void DungeonLevel::EnterStage()
{

	AddText(L"던전에 입장합니다.");


	Welcome();
	InputSystem::Clear();
}

void DungeonLevel::BackToVillage()
{
	AddText(L"때로는 한발 물러서는 것이 현명할 수 있습니다....");
	AddText(L"당신은 발걸음을 돌려 마을로 돌아갑니다...");

	Welcome();
	InputSystem::Clear();
}



void DungeonLevel::AddText(const wstring& text)
{
	m_systemTexts.push_back(text);
}

void DungeonLevel::ClearText()
{
	m_systemTexts.clear();
}