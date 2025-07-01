#pragma once
#include "BaseLevel.h"

class VillageLevel : public BaseLevel
{
public:
	using BaseLevel::BaseLevel;
	virtual ~VillageLevel() = default;

private:

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
	void OnExitVillage();
};

