#include "Game.h"  
#include "Manager/LevelManager.h"
#include "Util/InputSystem.h"
#include "Util/Timer.h"  
#include "Core/GameInstance.h"
#include "Screen.h"

Game::~Game() noexcept  
{  
	Release();  
}  

bool Game::Init()  
{  
	
	m_screen->Init();
	GameInstance::GetInstance()->Init();
	LevelManager::GetInstance()->Init();

	return true;
}  

void Game::Run()  
{  
	Timer::Init();  
	Init();

	while (true)  
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
	InputSystem::Update();
}  

void Game::Update()  
{  
	LevelManager::GetInstance()->Update();
}  

void Game::Render()  
{  
	m_screen->Clear();

	LevelManager::GetInstance()->Render(m_screen);

	m_screen->SwapBuffer();
}  

void Game::Release()  
{  
	LevelManager::GetInstance()->Release();

	m_screen->Release();
}
