#include "TitleLevel.h"
#include "../Core/GameInstance.h"
#include "../Util/InputSystem.h"
#include "../Core/LevelManager.h"


void TitleLevel::Init()
{
	ProcessTitleMenu();

	BaseLevel::Init();
}



void TitleLevel::SetTitleLevel()
{
	GameInstance::GetInstance()->UpdateLevelName(GetTag());
}

void TitleLevel::ProcessTitleMenu()
{
	GameInstance* gameInstance = GameInstance::GetInstance();
	gameInstance->ClearText();

	gameInstance->EnqueueText(L"============================================");
	gameInstance->EnqueueText(L"당신의 모험을 시작합니다.");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"[메뉴 옵션]");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"1. 마을로 들어가기");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"2. 던전으로 이동하기");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"3. 게임 종료");
	gameInstance->EnqueueText(L"");
	gameInstance->EnqueueText(L"============================================");
	gameInstance->EnqueueText(L"원하는 옵션의 번호를 입력하세요.");

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
			GameInstance::GetInstance()->EnqueueText(L"잘못된 입력입니다. 다시 시도하세요.");
			ProcessTitleMenu();
		}
	);
}

void TitleLevel::OnEnterVillage()
{
	GameInstance::GetInstance()->EnqueueText(L"마을로 입장합니다...");

	LevelManager::GetInstance()->SetNextLevel(L"Village"); 
	BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();

	InputSystem::Clear();
}

void TitleLevel::OnEnterDungeon()
{
	GameInstance::GetInstance()->EnqueueText(L"끝없는 모험이 당신을 반깁니다...");

	LevelManager::GetInstance()->SetNextLevel(L"Dungeon");
	BaseLevel* nextLevel = LevelManager::GetInstance()->GetNextLevel();

	InputSystem::Clear();
}

void TitleLevel::OnQuitGame()
{
	GameInstance::GetInstance()->EnqueueText(L"무한 지옥에 오신 것을 환영합니다.");
	GameInstance::GetInstance()->EnqueueText(L"ㅎㅎ 장난이에요");

	exit(0); // exit game
}

