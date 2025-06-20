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
	static bool IsKeyPressed(EKeyCode key);

	static InputAction* CreateAction(const string& actionName);
	static void BindAction(const string& actionName, uint8 key);
	static void ClearBinding(uint8 key);
	static void ClearAllBindings();

};

