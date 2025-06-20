#pragma once
#include "../Common.h"
#include "InputAction.h"



class InputSystem
{
public:
	InputSystem() = delete;
	~InputSystem() = delete;

private:
	static bool m_currentKeyStates[256];
	static bool m_previousKeyStates[256];

	static unordered_map<string, InputAction*> m_actions;
	static unordered_map<int8, string> m_keyToActionMap;

private:
	static string GetKeyName(const int8& vkey);

public:
	static void Update();
	static bool IsKeyPressed(const int8& vkey);

	static InputAction* CreateAction(const string& actionName);
	static void BindAction(const string& actionName, int8 key);
	static void ClearBinding(int8 key);
	static void ClearAllBindings();

};

