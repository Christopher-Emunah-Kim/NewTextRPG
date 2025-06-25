#pragma once
#include "../Common.h"
#include "InputAction.h"



class InputSystem
{
public:
	InputSystem() = delete;
	~InputSystem() = delete;

private:
	static wstring m_inputBuffer;
	static wstring m_command;
	static bool m_bIsAcceptingTextInput;
	static bool m_bIsTextInputMode;

	static bool m_currentKeyStates[256];
	static bool m_previousKeyStates[256];

	static unordered_map<wstring, InputAction*> m_actions;
	static unordered_map<int8, wstring> m_keyToActionMap;


private:
	static wstring GetKeyName(const int8& vkey);

public:
	static void Update();
	static bool IsKeyPressed(EKeyCode key);

	static void StartTextInput();
	static void StopTextInput();
	static bool IsTextInputMode();
	static bool IsAcceptingTextInput();
	static void SetTextInputMode(bool isTextInputMode);
	static const wstring& GetInputBuffer();
	static const wstring GetCommand();
	static void ProcessControlInput();
	static void ProcessTextInput();

	static InputAction* CreateAction(const wstring& actionName);
	static void BindAction(const wstring& actionName, uint8 key);
	static void ClearBinding(uint8 key);
	static void ClearAllBindings();

};

