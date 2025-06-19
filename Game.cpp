#include "Game.h"  
#include "Util/InputSystem.h"
#include "Util/Timer.h"  

Game::~Game() noexcept  
{  
	Release();  
}  

bool Game::Init()  
{  

}  

void Game::Run()  
{  
	Timer::Init();  

	while (true)  
	{  
		//레벨매니저 레벨 변경  

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
