#pragma once
#include "BaseComponent.h"

class RendererComp : public BaseComponent
{
public:
	RendererComp(BaseGameObject* owner, const wstring& renderShape);

private:
	wstring m_renderShape;

public: 
	virtual void Render(Screen* screen) override;
};

