#include "InputSystem.h"
#include "InputAction.h"
#include "../Common.h"

bool InputSystem::m_currentKeyStates[256] = { false };
bool InputSystem::m_previousKeyStates[256] = { false };

unordered_map<string, InputAction*> InputSystem::m_actions;
unordered_map<int8, string> InputSystem::m_keyToActionMap;



string InputSystem::GetKeyName(const int8& vkey)
{
	if ((vkey >= 'A' && vkey <= 'Z') || (vkey >= '0' && vkey <= '9'))
	{
		char keyChar = static_cast<char>(vkey);
		return string(1, keyChar);
	}
	return "";
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

	for (int i = 0; i < static_cast<int>(sizeof(m_currentKeyStates)); ++i)
	{
		if (m_currentKeyStates[i] == true && m_previousKeyStates[i] == false) //PRESSED
		{
            unordered_map<int8, string>::iterator it = m_keyToActionMap.find(i);  

            if (it != m_keyToActionMap.end())  
            {  
				unordered_map<string, InputAction*>::iterator actionIt = m_actions.find(it->second);
                
				if (actionIt != m_actions.end())  
                {  
                    actionIt->second->ExecuteCallBack(EInputEvent::PRESSED);
                }  
            }
		}
		else if (m_currentKeyStates[i] == false && m_previousKeyStates[i] == true) //RELEASED
		{
			unordered_map<int8, string>::iterator it = m_keyToActionMap.find(i);

			if (it != m_keyToActionMap.end())
			{
				unordered_map<string, InputAction*>::iterator actionIt = m_actions.find(it->second);

				if (actionIt != m_actions.end())
				{
					actionIt->second->ExecuteCallBack(EInputEvent::RELEASED);
				}
			}
		}
		else if (m_currentKeyStates[i] == true && m_previousKeyStates[i] == true) //HOLD
		{
			unordered_map<int8, string>::iterator it = m_keyToActionMap.find(i);

			if (it != m_keyToActionMap.end())
			{
				unordered_map<string, InputAction*>::iterator actionIt = m_actions.find(it->second);

				if (actionIt != m_actions.end())
				{
					actionIt->second->ExecuteCallBack(EInputEvent::HOLD);
				}
			}
		}

	}

}

bool InputSystem::IsKeyPressed(EKeyCode key)
{
	return (GetAsyncKeyState(static_cast<int>(key)) & 0x8000) != 0;
}

InputAction* InputSystem::CreateAction(const string& actionName)
{
	unordered_map<string, InputAction*>::iterator it = m_actions.find(actionName);
	
	if (it != m_actions.end())
	{
		return it->second; 
	}

	InputAction* newAction = new InputAction(actionName);

	m_actions[actionName] = newAction;

	return newAction;
}

void InputSystem::BindAction(const string& actionName, uint8 key)
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

	for (unordered_map<string, InputAction*>::iterator it = m_actions.begin(); it != m_actions.end(); ++it)
	{
        pair<string, InputAction*> action = *it;
		delete action.second;
	}
	m_actions.clear();
}
