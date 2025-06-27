#include "EquipmentComp.h"
#include "../../Util/Type/EnumType.h"

EquipmentComp::EquipmentComp(BaseGameObject* owner)
	: BaseComponent(owner)
{
}

EquipmentComp::~EquipmentComp()
{
}


bool EquipmentComp::EquipItem(const wstring& itemId, EItemType itemType)
{
	return true;
}