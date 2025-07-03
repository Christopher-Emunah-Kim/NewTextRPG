#pragma once
#include "Common.h"
#include "Screen.h"

class Screen;

class Game
{
public:
	//explicit Game() : m_screen(Screen::GetInstance()) { }
	virtual ~Game() noexcept;

public:
	bool Init();
	void Run();

private:
	void ProcessInput();
	void Update();
	void Render();
	void Release();

private:
	Screen m_screen;

};

