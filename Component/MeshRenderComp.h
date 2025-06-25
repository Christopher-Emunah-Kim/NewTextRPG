#pragma once
#include "BaseComponent.h"

class MeshRenderComp : public BaseComponent
{
public:
	MeshRenderComp(BaseGameObject* owner, const wstring& renderShape);

private:
	wstring m_renderShape;

public: 
	virtual void Render(Screen* screen) override;
};

