#pragma once
#include "../BaseComponent.h"

class MeshUIComp : public BaseComponent
{
public:
	MeshUIComp(BaseGameObject* owner, const wstring& renderShape);

private:
	wstring m_renderShape;

public: 
	virtual void Render(Screen* screen) override;
};

