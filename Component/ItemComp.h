#pragma once
#include "BaseComponent.h"

class ItemComp : public BaseComponent
{
public:
	ItemComp(BaseGameObject* owner);
	virtual ~ItemComp() = default;

private:
	int32 m_healAmount = 0;
	int32 m_buyValue = 0;
	int32 m_sellValue = 0;
	Status m_itemStatus;
	wstring m_itemType = L"";

public:
	virtual void Init() override;

	void UseHealItem(BaseGameObject* target);
	void UseEquipableItem(BaseGameObject* target);

	void SetItemStatus(const int32& atk, const int32& def, const int32& agi);

	inline void SetHealAmount(const int32& amount) noexcept { m_healAmount = amount; }
	inline void SetBuyValue(const int32& value) noexcept { m_buyValue = value; }
	inline void SetSellValue(const int32& value) noexcept { m_sellValue = value; }
	inline void SetItemType(const wstring& type) noexcept { m_itemType = type; }

	inline int32 GetHealAmount() noexcept { return m_healAmount; }
	inline int32 GetBuyValue() noexcept { return m_buyValue; }
	inline int32 GetSellValue() noexcept { return m_sellValue; }
	inline Status GetItemStatus() noexcept { return m_itemStatus; }
	inline wstring GetItemType() noexcept { return m_itemType; }
};

