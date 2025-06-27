#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/EnumType.h"

class EquipmentComp final : public BaseComponent
{
public:
	EquipmentComp(BaseGameObject* owner);
	virtual ~EquipmentComp();

private:


public:

	bool EquipItem(const wstring& itemId, EItemType itemType);
};

