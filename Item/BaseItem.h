﻿#pragma once
#include "../Common.h"
#include "../Util/Type/Status.h"
#include "../Util/Type/EnumType.h"

constexpr int16 DEFAULT_ITEM_MAX_COUNT = 99;

class BaseItem
{
public:
	explicit BaseItem()
		: m_itemId(10000), m_name(L"Unknown Item"), m_itemType(EItemType::None), m_description(L"Unknown Item"),
		m_buyingPrice(0), m_sellingPrice(0), m_attack(0), m_defense(0), m_agility(0), m_count(0), m_maxCount(DEFAULT_ITEM_MAX_COUNT)
	{	}

	explicit BaseItem(const int32& id, const wstring& name, EItemType itemType, const wstring& description,
		const int16& buyingPrice, const int16& sellingPrice,
		const int16& attack = 0, const int16& defense = 0, const int16& agility = 0)
		: m_itemId(id), m_name(name), m_itemType(itemType), m_description(description),
		m_buyingPrice(buyingPrice), m_sellingPrice(sellingPrice),
		m_attack(attack), m_defense(defense), m_agility(agility), m_count(0), m_maxCount(DEFAULT_ITEM_MAX_COUNT)
	{	}

	virtual ~BaseItem() = default;

	inline const wstring& GetDescription() const noexcept { return m_description; }
	inline const wstring& GetName() const noexcept { return m_name; }
	inline int32 GetItemID() const noexcept { return m_itemId; }
	inline int16 GetBuyingPrice() const noexcept { return m_buyingPrice; }
	inline int16 GetSellingPrice() const noexcept { return m_sellingPrice; }
	inline EItemType GetItemType() const noexcept { return m_itemType; }
	inline Status GetItemStatus() const noexcept { return Status::NewStatus(m_attack, m_defense, m_agility); }

private:
	int32 m_itemId;
	wstring m_name;
	EItemType m_itemType;
	wstring m_description;
	int16 m_buyingPrice;
	int16 m_sellingPrice;
	int16 m_attack;
	int16 m_defense;
	int16 m_agility;
	int16 m_count;
	int16 m_maxCount = DEFAULT_ITEM_MAX_COUNT;
};
