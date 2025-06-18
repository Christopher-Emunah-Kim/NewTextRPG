#include "Game.h"
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
}

void Game::Update()
{
}

void Game::Render()
{
}

void Game::Release()
{
}
