#pragma once
#include "../Common.h"
#include "../Util/Type/StatusType.h"
#include "../Util/Type/EnumType.h"

class BaseItem
{
public:
	BaseItem()
		: m_name(L"Unknown Item"), m_itemType(EItemType::None), m_description(L"Unknown Item"),
		m_buyingPrice(0), m_sellingPrice(0), m_attack(0), m_defense(0), m_agility(0), m_count(0), m_maxCount(1) 
	{	}

	BaseItem(const wstring& name, EItemType itemType, const wstring& description,
		const int16& buyingPrice, const int16& sellingPrice,
		const int16& attack = 0, const int16& defense = 0, const int16& agility = 0)
		: m_name(name), m_itemType(itemType), m_description(description),
		m_buyingPrice(buyingPrice), m_sellingPrice(sellingPrice),
		m_attack(attack), m_defense(defense), m_agility(agility), m_count(0), m_maxCount(1)
	{	}

	virtual ~BaseItem() = default;

private:
	wstring m_name;
	EItemType m_itemType;
	wstring m_description;
	int16 m_buyingPrice;
	int16 m_sellingPrice;
	int16 m_attack;
	int16 m_defense;
	int16 m_agility;
	int16 m_count;
	int16 m_maxCount;

public:
	virtual BaseItem* CreateItem() const
	{
		return new BaseItem(*this);
	}

	bool AddItemCount(int16 count = 1)
	{
		if (m_count + count > m_maxCount)
		{
			return false;
		}
		m_count += count;
		return true;
	}

	bool RemoveItemCount(int16 count = 1)
	{
		if (m_count < count)
		{
			return false;
		}
		m_count -= count;
		return true;
	}

	Status GetItemStatus() const 
	{
		return Status::NewStatus(m_attack, m_defense, m_agility);
	}

	inline bool IsFull() const { return m_count >= m_maxCount; }
	inline bool IsEmpty() const { return m_count <= 0; }

	inline void SetMaxCount(const int16& maxCount) { m_maxCount = maxCount; }

	inline const wstring& GetName() const noexcept { return m_name; }
	inline const EItemType& GetItemType() const noexcept { return m_itemType; }
	inline const wstring& GetDescription() const noexcept { return m_description; }
	inline const int16& GetBuyingPrice() const noexcept { return m_buyingPrice; }
	inline const int16& GetSellingPrice() const noexcept { return m_sellingPrice; }
	inline const int16& GetAttack() const noexcept { return m_attack; }
	inline const int16& GetDefense() const noexcept { return m_defense; }
	inline const int16& GetAgility() const noexcept { return m_agility; }
	inline const int16& GetCount() const noexcept { return m_count; }
	inline const int16& GetMaxCount() const noexcept { return m_maxCount; }
};
