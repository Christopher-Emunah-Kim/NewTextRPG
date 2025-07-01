#pragma once
#include "../BaseComponent.h"
#include "../../Util/Type/EnumType.h"
#include "../../Item/BaseItem.h"

class EquipmentComp final : public BaseComponent
{
public:
	EquipmentComp(BaseGameObject* owner);
	virtual ~EquipmentComp();

private:
	BaseItem* m_weaponSlot;
	BaseItem* m_armorSlot;

public:
	virtual void Release() override;

	bool EquipItem(BaseItem* item);
	bool IsEquipped(EItemType itemType) const;
	BaseItem* UnequipItem(EItemType itemType);
	BaseItem* GetEquippedItem(EItemType itemType) const;
};

