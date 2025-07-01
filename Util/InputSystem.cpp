#include "InputSystem.h"

wstring InputSystem::s_inputBuffer;
unordered_map<wstring, InputAction> InputSystem::s_actions;
InputAction InputSystem::s_actionOnError;

void InputSystem::ProcessTextInput()
{
	while (_kbhit())
	{
		wchar_t wch = _getwch();

		switch (wch)
		{
		case L'\r':
		{
			ProcessAction(std::move(s_inputBuffer));
		}
		break;
		case L'\b':
		{
			if (false == s_inputBuffer.empty())
			{
				s_inputBuffer.pop_back();
			}
		}
		break;

		default:
		{
			s_inputBuffer.push_back(wch);
		}
			break;
		}
	}
}

void InputSystem::BindActionOnInputError(InputAction action)
{
	s_actionOnError = action;
}

void InputSystem::BindAction(const wstring& command, InputAction action)
{
	s_actions[command] = action;
}

void InputSystem::BindAction(initializer_list<pair<wstring, InputAction>> actions)
{
	for (initializer_list<pair<wstring, InputAction>>::const_iterator it = actions.begin(); it != actions.end(); ++it)
	{
		s_actions[it->first] = it->second;
	}
}

void InputSystem::Clear()
{
	s_actions.clear();
	s_actionOnError = nullptr;
}

void InputSystem::Clear(const wstring& command)
{
	s_actions.erase(command);
}

const wstring& InputSystem::GetBuffer()
{
	return s_inputBuffer;
}

void InputSystem::ProcessAction(wstring command)
{
	unordered_map<wstring, InputAction>::iterator it = s_actions.find(command);

	if (it != s_actions.end())
	{
		it->second(); // Execute the bound action
	}
	else
	{
		s_actionOnError();
	}
}