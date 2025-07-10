#pragma once
#include "../Util/Type/EnumType.h"
#include "../Util/Type/StatusType.h"


class Equipment final
{
public:
	explicit Equipment();
	virtual ~Equipment();

	void Release();
	bool EquipItem(int32 itemId);
	int32 UnequipItem(EItemType itemType);
	int32 GetEquippedItem(EItemType itemType) const;
	Status GetTotalEquipmentStatus() const;

private:
	int32 m_weaponItemId;
	int32 m_armorItemId;
};

