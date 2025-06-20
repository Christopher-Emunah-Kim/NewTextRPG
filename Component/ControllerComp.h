#pragma once
#include "BaseComponent.h"

class ControllerComp : public BaseComponent
{

public:
	using BaseComponent::BaseComponent;
	virtual void Update() override;

	void ApplyInputToPosition(LONG& currentY, LONG& currentX);

};

