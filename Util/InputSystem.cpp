#include "InputSystem.h"
#include "../Common.h"

bool InputSystem::m_currentKeyStates[256] = { false };
bool InputSystem::m_previousKeyStates[256] = { false };




string InputSystem::GetKeyName(int vkey)
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


	//test
	for (int i = 0; i < static_cast<int>(sizeof(m_currentKeyStates)); ++i)
	{
		if (m_currentKeyStates[i] == true && m_previousKeyStates[i] == false)
		{
			std::cout << InputSystem::GetKeyName(i) << " 키가 눌렸습니다." << std::endl;
		}
	}

}
