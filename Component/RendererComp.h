#pragma once
#include "BaseComponent.h"

class RendererComp : public BaseComponent
{
public:
	RendererComp(BaseGameObject* owner, const string& renderShape);

private:
	string m_renderShape;

public: 
	virtual void Render() override;
};

