#include "InputSystem.h"

wstring InputSystem::m_inputBuffer;
unordered_map<wstring, InputAction> InputSystem::m_actions;
InputAction InputSystem::m_actionOnError;

void InputSystem::ProcessTextInput()
{
	while (_kbhit())
	{
		wchar_t wch = _getwch();

		switch (wch)
		{
		case L'\r':
		{
			ProcessAction(std::move(m_inputBuffer));
		}
		break;
		case L'\b':
		{
			if (false == m_inputBuffer.empty())
			{
				m_inputBuffer.pop_back();
			}
		}
		break;

		default:
		{
			m_inputBuffer.push_back(wch);
		}
			break;
		}
	}
}

void InputSystem::BindActionOnInputError(InputAction action)
{
	m_actionOnError = action;
}

void InputSystem::BindAction(const wstring& command, InputAction action)
{
	m_actions[command] = action;
}

void InputSystem::BindAction(initializer_list<pair<wstring, InputAction>> actions)
{
	for (initializer_list<pair<wstring, InputAction>>::const_iterator it = actions.begin(); it != actions.end(); ++it)
	{
		m_actions[it->first] = it->second;
	}
}

void InputSystem::Clear()
{
	m_actions.clear();
	m_actionOnError = nullptr;
}

void InputSystem::Clear(const wstring& command)
{
	m_actions.erase(command);
}

const wstring& InputSystem::GetBuffer()
{
	return m_inputBuffer;
}

void InputSystem::ProcessAction(wstring command)
{
	unordered_map<wstring, InputAction>::iterator it = m_actions.find(command);

	if (it != m_actions.end())
	{
		it->second(); // Execute the bound action
	}
	else if(m_actionOnError)
	{
		m_actionOnError();
	}

}