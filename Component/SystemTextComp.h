#pragma once
#include "BaseComponent.h"
#include <queue>

constexpr int32 DEFAULT_BASE_Y = 5;
constexpr int32 MAX_LINES = 20;

class SystemTextComp : public BaseComponent
{
public:
	SystemTextComp(BaseGameObject* owner);
	virtual ~SystemTextComp() = default;

private:
	queue<wstring> m_textQueue;


public:
	virtual void Render(Screen* screen) override;

	void SetText(const wstring& text);

	void EnqueueText(const wstring& text);

	void ClearTexts();

};

