#pragma once
#include "../BaseComponent.h"

class MeshUIComp final : public BaseComponent
{
public:
	MeshUIComp(BaseGameObject* owner, const wstring& renderShape);

private:
	wstring m_renderShape;

public: 
	virtual void Render(Screen* screen) override;
};

