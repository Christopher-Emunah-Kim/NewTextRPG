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

	static unordered_map<wstring, InputAction*> m_actions;
	static unordered_map<int8, wstring> m_keyToActionMap;


private:
	static wstring GetKeyName(const int8& vkey);

public:
	static void Update();
	static bool IsKeyPressed(EKeyCode key);

	static InputAction* CreateAction(const wstring& actionName);
	static void BindAction(const wstring& actionName, uint8 key);
	static void ClearBinding(uint8 key);
	static void ClearAllBindings();

};

