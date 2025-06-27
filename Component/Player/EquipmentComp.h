#pragma once
#include "../BaseComponent.h"

class EquipmentComp final : public BaseComponent
{
public:
	EquipmentComp(BaseGameObject* owner);
	virtual ~EquipmentComp();
};

