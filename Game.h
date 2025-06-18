#pragma once
#include "Common.h"

class Game
{
public:
	virtual ~Game() noexcept;

	bool Init();
	void Run();

private:
	void ProcessInput();
	void Update();
	void Render();
	void Release();

};

