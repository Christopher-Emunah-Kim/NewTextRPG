#pragma once
#include "BaseLevel.h"

class VillageLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~VillageLevel() = default;

private:
	int32 healerCost = 100;

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

