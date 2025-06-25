#pragma once
#include "../BaseComponent.h"
#include <queue>

constexpr int32 MAX_LINES = 10;
constexpr int32 DEFAULT_BASE_Y = SCREEN_HEIGHT - MAX_LINES - 1;

class SystemTextUIComp : public BaseComponent
{
public:
	SystemTextUIComp(BaseGameObject* owner);
	virtual ~SystemTextUIComp() = default;

private:
	queue<wstring> m_textQueue;


public:
	virtual void Render(Screen* screen) override;

	void SetText(const wstring& text);

	void EnqueueText(const wstring& text);

	void ClearTexts();

};

