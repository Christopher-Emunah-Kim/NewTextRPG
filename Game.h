#pragma once
#include "Common.h"
#include "Screen.h"

class Screen;

class Game
{
public:
	explicit Game() : m_screen(Screen::GetInstance()) { }
	virtual ~Game() noexcept;

private:
	Screen* m_screen;

public:
	bool Init();
	void Run();

private:
	void ProcessInput();
	void Update();
	void Render();
	void Release();

};

