#pragma once
#include "../Common.h"

using InputAction = function<void()>;

class InputSystem
{
private:
	static void ProcessAction(wstring command);

public:
	static void ProcessTextInput();
	static void BindActionOnInputError(InputAction action);
	static void BindAction(const wstring& command, InputAction action);
	static void BindAction(initializer_list<pair<wstring, InputAction>> actions);
	static void Clear();
	static void Clear(const wstring& command);

	static const wstring& GetBuffer();

private:
	static wstring m_inputBuffer;
	static unordered_map<wstring, InputAction> m_actions;
	static InputAction m_actionOnError;
};