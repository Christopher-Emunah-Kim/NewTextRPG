#include "Game.h"  
#include "Core/LevelManager.h"
#include "Util/InputSystem.h"
#include "Util/Timer.h"  
#include "Core/GameInstance.h"
#include "Data/ItemDataTable.h"
#include "Data/PlayerDataTablePerLevel.h"
#include "Data/MonsterDataTable.h"
#include "Screen.h"

Game::~Game() noexcept  
{  
	Release();  
}  

bool Game::Init()  
{  
	PlayerLevelPropertiesTable::GetInstance()->Init();
	m_screen.Init();
	ItemDataTable::GetInstance()->Init();
	MonsterDataTable::GetInstance()->Init();
	LevelManager::GetInstance()->Init();

	return true;
}  

void Game::Run()  
{  
	Timer::Init();  

	while (!GameInstance::GetInstance()->ShouldQuit())  
	{  
		if (LevelManager::GetInstance()->IsSetNextLevel())
		{
			LevelManager::GetInstance()->ChangeLevel();
		}

		if (Timer::CanUpdate())  
		{  
			ProcessInput();  
			Update();  
			Render();  
		}  
	}  
}  

void Game::ProcessInput()  
{  
	InputSystem::ProcessTextInput();
}  

void Game::Update()  
{  
	LevelManager::GetInstance()->Update();
}  

void Game::Render()  
{  
	m_screen.Clear();

	GameInstance::GetInstance()->RenderHud(m_screen);

	m_screen.SwapBuffer();
}  

void Game::Release()  
{  
	LevelManager::GetInstance()->Release();

	m_screen.Release();
}
