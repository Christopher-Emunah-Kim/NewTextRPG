#include "Game.h"  
#include "Manager/LevelManager.h"
#include "Util/InputSystem.h"
#include "Util/Timer.h"  

Game::~Game() noexcept  
{  
	Release();  
}  

bool Game::Init()  
{  
	//BaseLevel* titleLevel

	return true;
}  

void Game::Run()  
{  
	Timer::Init();  

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
	//레벨 매니저 통해 레벨과 오브젝트들 업데이트
}  

void Game::Render()  
{  
	//레벨 매니저 통해 레벨과 오브젝트들 렌더
}  

void Game::Release()  
{  

}
