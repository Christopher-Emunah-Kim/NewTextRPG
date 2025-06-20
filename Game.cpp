#include "Game.h"  
#include "Manager/LevelManager.h"
#include "Util/InputSystem.h"
#include "Util/Timer.h"  
#include "Screen.h"

Game::~Game() noexcept  
{  
	Release();  
}  

bool Game::Init()  
{  
	Screen::GetInstance()->Init();
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
	Screen::GetInstance()->Clear();

	LevelManager::GetInstance()->Render();

	Screen::GetInstance()->SwapBuffer();
}  

void Game::Release()  
{  
	LevelManager::GetInstance()->Release();
	Screen::GetInstance()->Release();
}
