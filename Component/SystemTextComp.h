#pragma once
#include "BaseComponent.h"

class SystemTextComp : public BaseComponent
{
public:
	SystemTextComp(BaseGameObject* owner);
	virtual ~SystemTextComp() = default;

private:
	string m_systemText;

public:
	virtual void Render(Screen* screen) override;

	void SetText(const string& text);

	inline const string& GetText() const { return m_systemText; }
};

