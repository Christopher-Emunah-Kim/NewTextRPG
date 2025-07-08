#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Util/InputSystem.h"
#include "../Core/LevelManager.h"


void TitleLevel::Init()
{
	gi = GameInstance::GetInstance();

	ProcessTitleMenu();

	BaseLevel::Init();
}



void TitleLevel::SetTitleLevel()
{
	gi->UpdateLevelName(GetTag());
}

void TitleLevel::ProcessTitleMenu()
{
	
	gi->ClearText();

	gi->WriteLine(L"============================================");
	gi->WriteLine(L"당신의 모험을 시작합니다.");
	gi->WriteLine(L"");
	gi->WriteLine(L"[메뉴 옵션]");
	gi->WriteLine(L"");
	gi->WriteLine(L"1. 마을로 들어가기");
	gi->WriteLine(L"");
	gi->WriteLine(L"2. 던전으로 이동하기");
	gi->WriteLine(L"");
	gi->WriteLine(L"3. 게임 종료");
	gi->WriteLine(L"");
	gi->WriteLine(L"============================================");
	gi->WriteLine(L"원하는 옵션의 번호를 입력하세요.");

	InputSystem::BindAction(
		{
			{L"1", bind(&TitleLevel::OnEnterVillage, this)},
			{L"2", bind(&TitleLevel::OnEnterDungeon, this)},
			{L"3", bind(&TitleLevel::OnQuitGame, this)}
		}
	);

	InputSystem::BindActionOnInputError(
		[this]()
		{
			GameInstance::GetInstance()->ClearText();
			GameInstance::GetInstance()->WriteLine(L"잘못된 입력입니다. 다시 시도하세요.");
			ProcessTitleMenu();
		}
	);

}

void TitleLevel::OnEnterVillage()
{
	gi->WriteLine(L"마을로 입장합니다...");

	LevelManager::GetInstance()->SetNextLevel(L"Village"); 
	BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();

	InputSystem::Clear();
}

void TitleLevel::OnEnterDungeon()
{
	gi->WriteLine(L"끝없는 모험이 당신을 반깁니다...");

	LevelManager::GetInstance()->SetNextLevel(L"Dungeon");
	BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();

	InputSystem::Clear();
}

void TitleLevel::OnQuitGame()
{
	gi->WriteLine(L"게임을 종료합니다. 이용해 주셔서 감사합니다.");
	gi->WriteLine(L"아무 키나 누르면 종료됩니다...");

	InputSystem::Clear();

	gi->RequestShutdown();

	//exit(0); // exit game
}

