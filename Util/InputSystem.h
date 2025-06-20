#pragma once
#include "../Common.h"


class InputSystem
{
public:
	InputSystem() = delete;
	~InputSystem() = delete;

private:
	static bool m_currentKeyStates[256];
	static bool m_previousKeyStates[256];

private:
	static string GetKeyName(const int& vkey);

public:
	static void Update();

	static bool IsKeyPressed(const int& vkey);

};

