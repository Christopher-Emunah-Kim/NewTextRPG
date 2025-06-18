#pragma once
#include "../Common.h"


class InputManager
{
public:
	InputManager() = delete;
	~InputManager() = delete;

private:
	static bool m_currentKeyStates[256];
	static bool m_previousKeyStates[256];

private:
	static string GetKeyName(int vkey);

public:
	static void Update();



};

