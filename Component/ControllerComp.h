#pragma once
#include "BaseComponent.h"
#include "../Util/Type/EnumType.h"

class ControllerComp : public BaseComponent
{

public:
	using BaseComponent::BaseComponent;

	virtual void Init() override;
	virtual void Update() override;

	void HandleMovement(EInputEvent inputEvent, EMoveDirection direction);

};
