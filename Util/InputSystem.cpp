#include "InputSystem.h"
#include "InputAction.h"
#include "../Common.h"


wstring InputSystem::m_inputBuffer = L"";
wstring InputSystem::m_command = L"";
bool InputSystem::m_bIsAcceptingTextInput = false;
bool InputSystem::m_bIsTextInputMode = false;

bool InputSystem::m_currentKeyStates[256] = { false };
bool InputSystem::m_previousKeyStates[256] = { false };

unordered_map<wstring, InputAction*> InputSystem::m_actions;
unordered_map<int8, wstring> InputSystem::m_keyToActionMap;



wstring InputSystem::GetKeyName(const int8& vkey)
{
	if ((vkey >= 'A' && vkey <= 'Z') || (vkey >= '0' && vkey <= '9'))
	{
		char keyChar = static_cast<char>(vkey);
		return wstring(1, keyChar);
	}
	return L" ";
}

void InputSystem::Update()
{
	memcpy(m_previousKeyStates, m_currentKeyStates, sizeof(m_currentKeyStates));

	for (int vkey = 0; vkey < 256; ++vkey)
	{
		if (GetAsyncKeyState(vkey) & 0x8000)
		{
			m_currentKeyStates[vkey] = true;
		}
		else
		{
			m_currentKeyStates[vkey] = false;
		}
	}

	//Switch Input Mode
	if (!m_bIsTextInputMode && m_currentKeyStates[(uint8)EKeyCode::RETURN] == true && m_previousKeyStates[(uint8)EKeyCode::RETURN] == false)
	{
		m_bIsTextInputMode = true;
		StartTextInput();
		return;
	}

	if (false == m_bIsTextInputMode)
	{
		ProcessControlInput();
	}
	else
	{
		ProcessTextInput();
	}
}


bool InputSystem::IsKeyPressed(EKeyCode key)
{
	return (GetAsyncKeyState(static_cast<int>(key)) & 0x8000) != 0;
}

void InputSystem::StartTextInput()
{
	m_bIsAcceptingTextInput = true;
	m_bIsTextInputMode = true;
	m_inputBuffer.clear();
	m_command.clear();
}

void InputSystem::StopTextInput()
{
	m_bIsAcceptingTextInput = false;
	m_bIsTextInputMode = false;
	m_inputBuffer.clear();
}

bool InputSystem::IsTextInputMode()
{
	return m_bIsTextInputMode;
}

bool InputSystem::IsAcceptingTextInput()
{
	return m_bIsAcceptingTextInput;
}

void InputSystem::SetTextInputMode(bool isTextInputMode)
{
	m_bIsTextInputMode = isTextInputMode;
}

const wstring& InputSystem::GetInputBuffer()
{
	return m_inputBuffer;
}

const wstring InputSystem::GetCommand()
{
	wstring cmd = m_command;
	m_command.clear();
	return cmd;
}


void InputSystem::ProcessControlInput()
{
	for (int i = 0; i < static_cast<int>(sizeof(m_currentKeyStates)); ++i)
	{
		if (m_currentKeyStates[i] == true && m_previousKeyStates[i] == false) //PRESSED
		{
			unordered_map<int8, wstring>::iterator it = m_keyToActionMap.find(i);

			if (it != m_keyToActionMap.end())
			{
				unordered_map<wstring, InputAction*>::iterator actionIt = m_actions.find(it->second);

				if (actionIt != m_actions.end())
				{
					actionIt->second->ExecuteCallBack(EInputEvent::PRESSED);
				}
			}
		}
		else if (m_currentKeyStates[i] == false && m_previousKeyStates[i] == true) //RELEASED
		{
			unordered_map<int8, wstring>::iterator it = m_keyToActionMap.find(i);

			if (it != m_keyToActionMap.end())
			{
				unordered_map<wstring, InputAction*>::iterator actionIt = m_actions.find(it->second);

				if (actionIt != m_actions.end())
				{
					actionIt->second->ExecuteCallBack(EInputEvent::RELEASED);
				}
			}
		}
		else if (m_currentKeyStates[i] == true && m_previousKeyStates[i] == true) //HOLD
		{
			unordered_map<int8, wstring>::iterator it = m_keyToActionMap.find(i);

			if (it != m_keyToActionMap.end())
			{
				unordered_map<wstring, InputAction*>::iterator actionIt = m_actions.find(it->second);

				if (actionIt != m_actions.end())
				{
					actionIt->second->ExecuteCallBack(EInputEvent::HOLD);
				}
			}
		}
	}
}

void InputSystem::ProcessTextInput()
{
	if (false == m_bIsAcceptingTextInput)
		return;

	while (_kbhit())
	{
		wchar_t wch = _getwch();

		if (wch == L'\r') //Enter
		{
			if (m_inputBuffer.empty() == false)
			{
				m_command = m_inputBuffer;
				m_inputBuffer.clear();
				m_bIsTextInputMode = false;
			}
		}
		else if (wch == L'\b') //BaseSpace
		{
			if (m_inputBuffer.empty() == false)
			{
				m_inputBuffer.pop_back();
			}
		}
		else
		{
			m_inputBuffer += wch;
		}
	}
}

InputAction* InputSystem::CreateAction(const wstring& actionName)
{
	unordered_map<wstring, InputAction*>::iterator it = m_actions.find(actionName);
	
	if (it != m_actions.end())
	{
		return it->second; 
	}

	InputAction* newAction = new InputAction(actionName);

	m_actions[actionName] = newAction;

	return newAction;
}

void InputSystem::BindAction(const wstring& actionName, uint8 key)
{
	ClearBinding(key);

	m_keyToActionMap[key] = actionName;
}

void InputSystem::ClearBinding(uint8 key)
{
	m_keyToActionMap.erase(key);
}

void InputSystem::ClearAllBindings()
{
	m_keyToActionMap.clear();

	for (unordered_map<wstring, InputAction*>::iterator it = m_actions.begin(); it != m_actions.end(); ++it)
	{
        pair<wstring, InputAction*> action = *it;
		delete action.second;
	}
	m_actions.clear();
}
