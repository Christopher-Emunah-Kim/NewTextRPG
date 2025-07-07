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
	BaseItem* UnequipItem(EItemType itemType);
	BaseItem* GetEquippedItem(EItemType itemType) const;
	Status GetTotalEquipmentStatus() const;

private:
	BaseItem* m_weaponSlot;
	BaseItem* m_armorSlot;
};

