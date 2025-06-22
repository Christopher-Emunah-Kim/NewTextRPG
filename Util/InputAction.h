#pragma once
#include "../Common.h"
#include "Type/EnumType.h"


using InputActionCallback = std::function<void(EInputEvent)>;


class InputAction
{
public:
	InputAction(const wstring& actionName) : actionName(actionName) {}

private:
	wstring actionName;
	InputActionCallback m_callbackFuncPtr;

public:
	const wstring& GetActionName() const { return actionName; }

	void BindCallback(InputActionCallback callback)
	{
		m_callbackFuncPtr = callback;
	}

	void ExecuteCallBack(EInputEvent eventType) const 
	{
		if (m_callbackFuncPtr)
		{
			m_callbackFuncPtr(eventType);
		}
	}
};

