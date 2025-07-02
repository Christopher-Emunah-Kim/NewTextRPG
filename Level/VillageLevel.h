#pragma once
#include "BaseLevel.h"

constexpr __int32 HEALER_COST = 100;

class VillageLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~VillageLevel() = default;

private:
	int32 healerCost;

public:
	virtual void Init() override;
	virtual void Release() override;

private:
	void SetVillageStage();
	void Welcome();
	void OnEnterItemShop();
	void OnBuyItem();
	void BuySelectedItem(const wstring& itemName);
	void OnSellIItem();
	void OnEnterHealerShop();
	void OnRecoverPlayer();
	void OnExitVillage();
};

