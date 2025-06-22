#pragma once
#include "BaseComponent.h"

class SystemTextComp : public BaseComponent
{
public:
	SystemTextComp(BaseGameObject* owner);
	virtual ~SystemTextComp() = default;

private:
	wstring m_systemText;

public:
	virtual void Render(Screen* screen) override;

	void SetText(const wstring& text);

	inline const wstring& GetText() const { return m_systemText; }
};

