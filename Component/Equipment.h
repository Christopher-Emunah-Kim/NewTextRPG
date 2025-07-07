#pragma once
#include "BaseComponent.h"
#include "../Util/Type/EnumType.h"
#include "../Item/BaseItem.h"


class Equipment final
{
public:
	explicit Equipment();
	~Equipment();

	void Release();

	bool EquipItem(BaseItem* item);
	bool IsEquipped(EItemType itemType) const;
	BaseItem* UnequipItem(EItemType itemType);
	BaseItem* GetEquippedItem(EItemType itemType) const;
	Status GetTotalEquipmentStatus() const;

private:
	BaseItem* m_weaponSlot;
	BaseItem* m_armorSlot;
};

